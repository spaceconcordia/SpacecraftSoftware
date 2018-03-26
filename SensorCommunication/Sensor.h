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
    virtual ~Sensor();
protected:
    bool sendToOutputFile(string output);
    string receiveFromInput();
private:
    virtual string read()= 0;
    virtual bool write(string toWrite) = 0;
    string name;
    string address;
    unsigned long int samplingFrequency;
    ReadWrite action;
    string inputFileName;
    string outputFileName;
    bool currentlyRunning;
    CallBackTimer* timer;
    bool isFilenameAllowed(string filename);
};

#endif //SPACECRAFTSOFTWARE_SENSORS_H
