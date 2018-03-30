//
// Created by pbrink on 26/03/18.
//

#ifndef SPACECRAFTSOFTWARE_SAMPLESENSOR_H
#define SPACECRAFTSOFTWARE_SAMPLESENSOR_H


#include "Sensor.h"

class SampleSensor: public Sensor {
public:
    SampleSensor(string name, string address, unsigned long samplingFrequency, ReadWrite action,
                 string inputFileName, string outputFileName);
    ~SampleSensor() override {};
// private:
    void readFrom() override;
    void writeTo(string toWrite) override;
};


#endif //SPACECRAFTSOFTWARE_SAMPLESENSOR_H
