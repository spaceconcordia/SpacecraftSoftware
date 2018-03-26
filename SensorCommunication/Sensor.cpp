//
// Created by pbrink on 22/03/18.
//

#include <stdexcept>
#include <iostream>
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
        } else {
            throw std::invalid_argument("Invalid filename provided");
        }
    }
    if (action == ReadWrite::WRITE || action == ReadWrite::READ_WRITE) {
        if (isFilenameAllowed(inputFileName)) {
            this->inputFileName = inputFileName;
        } else {
            throw std::invalid_argument("Invalid filename provided");
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
        timer->start(samplingFrequency, std::bind(&Sensor::read, this));
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
}

bool Sensor::sendToOutputFile(string output) {
    // TODO: Switch to named pipes
    std::cout << output + " ";
}

string Sensor::receiveFromInput() {
    // TODO: Switch to named pipes
    return ".";
}
