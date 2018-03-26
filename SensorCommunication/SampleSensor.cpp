#include <iostream>
#include "SampleSensor.h"

//
// Created by pbrink on 26/03/18.
//
SampleSensor::SampleSensor(string name, string address, unsigned long samplingFrequency, ReadWrite action,
                           string inputFileName, string outputFileName) : Sensor(name, address, samplingFrequency,
                                                                                 action, inputFileName,
                                                                                 outputFileName) {}

string SampleSensor::read() {
    std::cout << "Enter an input: ";
    string input;
    std::cin >> input;
    return input;
}

bool SampleSensor::write(string toWrite) {
    std::cout << toWrite;
    // for validation purposes
    return true;
}
