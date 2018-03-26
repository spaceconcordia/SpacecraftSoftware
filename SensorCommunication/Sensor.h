//
// Created by pbrink on 22/03/18.
//

#ifndef SPACECRAFTSOFTWARE_SENSORS_H
#define SPACECRAFTSOFTWARE_SENSORS_H

#include <string>
#include "CallBackTimer.h"

using std::string;

enum class ReadWrite {
    READ,
    WRITE,
    READ_WRITE
};

class Sensor {
public:
    unsigned long SAMPLING_FREQUENCY_LOWER_LIMIT = 1; // 1 millisecond TODO: Determine a lower limit
    unsigned long SAMPLING_FREQUENCY_UPPER_LIMIT = 864000000; // 10 days TODO: Determine an upper limit
    Sensor(string name,
           string address,
           unsigned long int samplingFrequency,
           ReadWrite action,
           string inputFileName,
           string outputFileName);
    virtual ~Sensor();
    string getInputFilename() { return inputFileName; }
    string getOutputFilename() { return outputFileName; }
    unsigned long int getSamplingFrequency() { return samplingFrequency; }
    bool setSamplingFrequency(unsigned long int samplingFrequency);
    string getName() { return name; }
    string getAddress() { return address; }
    ReadWrite getAction() { return action; }
    bool isCurrentlyRunning() { return currentlyRunning; }
    bool startReading();
    bool stopReading();
    string receiveFromInput();
    virtual void writeTo(string toWrite) = 0;
protected:
    virtual void readFrom()= 0;
    void sendToOutput(string output);
private:
    string name;
    string address;
    unsigned long int samplingFrequency;
    ReadWrite action;
    string inputFileName;
    string outputFileName;
    bool currentlyRunning;
    CallBackTimer* timer;
    int fifoInput;
    int fifoOutput;
    bool createdFifoInput;
    bool createdFifoOutput;
    char readingFifoBuffer[512];
    bool isFilenameAllowed(string filename);
    bool createNamedPipe(string filename, bool forWriting);
};

#endif //SPACECRAFTSOFTWARE_SENSORS_H
