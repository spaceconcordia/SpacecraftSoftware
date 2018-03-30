#include <iostream>
#include "SampleSensor.h"

//
// Created by pbrink on 26/03/18.
//
SampleSensor::SampleSensor(string name, string address, unsigned long samplingFrequency, ReadWrite action,
                           string inputFileName, string outputFileName) : Sensor(name, address, samplingFrequency,
                                                                                 action, inputFileName,
                                                                                 outputFileName) {}

void SampleSensor::readFrom() {
    string input = receiveFromInput();
    writeTo(input);
}

void SampleSensor::writeTo(string toWrite) {
    sendToOutput(toWrite);
}
