//
// Created by pbrink on 22/03/18.
//

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Sensor.h"

Sensor::Sensor(string name,
               string address,
               unsigned long int samplingFrequency,
               ReadWrite action,
               string inputFileName,
               string outputFileName) :
                name(name), address(address), action(action)
{
    // ensure that input and output filenames are properly specified when necessary
    if (action == ReadWrite::READ || action == ReadWrite::READ_WRITE) {
        if (isFilenameAllowed(outputFileName)) {
            this->outputFileName = outputFileName;
            if (!createNamedPipe(outputFileName, true)) {
                throw std::invalid_argument("Invalid output filename provided");
            }
        } else {
            throw std::invalid_argument("Invalid output filename provided");
        }
    }
    if (action == ReadWrite::WRITE || action == ReadWrite::READ_WRITE) {
        if (isFilenameAllowed(inputFileName)) {
            this->inputFileName = inputFileName;
            if (!createNamedPipe(inputFileName, false)) {
                throw std::invalid_argument("Invalid input filename provided");
            }
        } else {
            throw std::invalid_argument("Invalid input filename provided");
        }
    }

    // validate sampling frequency
    if (samplingFrequency < SAMPLING_FREQUENCY_LOWER_LIMIT || samplingFrequency > SAMPLING_FREQUENCY_UPPER_LIMIT) {
        throw std::invalid_argument("Invalid sampling frequency provided");
    } else {
        this->samplingFrequency = samplingFrequency;
    }

    // create the callback timer
    timer = new CallBackTimer();
}

bool Sensor::isFilenameAllowed(string filename) {
    // TODO: verification of good filenames and paths
    return true;
}

bool Sensor::setSamplingFrequency(unsigned long int samplingFrequency) {
    if (samplingFrequency < SAMPLING_FREQUENCY_LOWER_LIMIT || samplingFrequency > SAMPLING_FREQUENCY_UPPER_LIMIT) {
        return false;
    } else {
        this->samplingFrequency = samplingFrequency;
    }
}

bool Sensor::startReading() {
    if (currentlyRunning) {
        return true;
    } else {
        timer->start(samplingFrequency, std::bind(&Sensor::readFrom, this));
        currentlyRunning = true;
    }
    return false;
}

bool Sensor::stopReading() {
    if (!currentlyRunning) {
        return true;
    } else {
        timer->stop();
        currentlyRunning = false;
    }
    return false;
}

Sensor::~Sensor() {
    delete timer;
    if (fifoInput != 0) {
        close(fifoInput);
        if (createdFifoInput) {
            // delete the named pipe we made
            unlink(inputFileName.c_str());
        }
    }
    if (fifoOutput != 0) {
        close(fifoOutput);
        if (createdFifoOutput) {
            // delete the named pipe we made
            unlink(outputFileName.c_str());
        }
    }
}

void Sensor::sendToOutput(string output) {
    // convert output to c_string
    const char* out = output.c_str();
    // open pipe
    ssize_t status;
    fifoOutput = open(outputFileName.c_str(), O_WRONLY);
    if (fifoOutput < 0) {
        printf("\n %s \n", strerror(errno));
    }
    // write to the pipe
    status = write(fifoOutput, out, strlen(out));
    if (status < 0) {
        printf("\n %s \n", strerror(errno));
    }
}

string Sensor::receiveFromInput() {
    // open pipe
    fifoInput = open(inputFileName.c_str(), O_RDONLY);
    if (fifoInput < 0) {
        printf("\n %s \n", strerror(errno));
    }
    // read from the pipe

    ssize_t status;
    status = read(fifoInput, readingFifoBuffer, 512);
    // TODO: for some reason this is returning 7 even though it is working properly. Figure out why
//    if (status != 0) {
//        printf("\n %s \n", strerror(errno));
//    }

    // look for \0 bytes (termination of c strings)
    // TODO: ensure that non c strings will not result in endless loops
    int index = 0;
    char result[512];
    while (readingFifoBuffer[index] != '\0') {
        result[index] = readingFifoBuffer[index];
        index++;
    }
    result[index] = '\0';
    return std::string(result);
}

bool Sensor::createNamedPipe(string filename, bool forWriting) {
    struct stat buffer;
    if (stat (filename.c_str(), &buffer) == 0) {
        // the file exists, check if it is a named pipe
        if (S_ISFIFO(buffer.st_mode)) {
            return true;
        } else {
            // the file already exists, but it is not a named pipe
            return false;
        }
    } else {
        // create the file
        int status;
        status = mkfifo(filename.c_str(), 0644);
        if (status != 0) {
            return false;
        } else {
            forWriting ? (createdFifoOutput = true) : (createdFifoInput = true);
            return true;
        }
    }
}
