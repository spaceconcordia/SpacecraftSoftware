//
// Created by pbrink on 22/03/18.
//

#include "Sensor.h"

Sensor::Sensor(string name,
               string address,
               float samplingFrequency,
               ReadWrite action,
               string inputFileName,
               string outputFileName) :
                name(name), address(address), samplingFrequency(samplingFrequency), action(action)
{
    // ensure that input and output filenames are properly specified when necessary
    if (action == ReadWrite::READ || action == ReadWrite::READ_WRITE) {
        if (isFilenameAllowed(outputFileName)) {
            this->outputFileName = outputFileName;
        } else {
            throw new 
        }
    }
}

bool Sensor::isFilenameAllowed(string filename) {
    // TODO: verification of good filenames and paths
    return true;
}
