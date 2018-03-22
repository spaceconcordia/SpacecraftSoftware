//
// Created by pbrink on 22/03/18.
//

#ifndef SPACECRAFTSOFTWARE_SENSORS_H
#define SPACECRAFTSOFTWARE_SENSORS_H

#include <string>

using std::string

class Sensor {
public:
    Sensor(string name,
           string address,
           float samplingFrequency,
           ReadWrite action,
           string inputFileName,
           string outputFileName);
    string getInputFilename() { return inputFileName; }
    string getOutputFilename() { return outputFileName; }
    float getSamplingFrequency() { return samplingFrequency; }
    bool setSamplingFrequency();
    string getName() { return name; }
    bool start();
    bool stop();
    virtual ~Sensor() = 0;
private:
    virtual string read()= 0;
    virtual string write() = 0;
    string name;
    string address;
    float samplingFrequency;
    ReadWrite action;
    string inputFileName;
    string outputFileName;

    bool isFilenameAllowed(string filename);
};

enum class ReadWrite {
    READ,
    WRITE,
    READ_WRITE
};

#endif //SPACECRAFTSOFTWARE_SENSORS_H
