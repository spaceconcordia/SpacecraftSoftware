//
// Created by pbrink on 15/11/17.
//

#ifndef RADIATIONTESTSRUNNER_TESTMATH_H
#define RADIATIONTESTSRUNNER_TESTMATH_H


#include "task.h"

class testMath : public task {
private:
    int iterations;
    const static int matrixSize = 100;
    int matrixA[matrixSize][matrixSize];
    int matrixB[matrixSize][matrixSize];
    int matrixC[matrixSize][matrixSize];
    void multiplyMatrices();
    void verifyMatrix();
    void resetResultMatrix();
public:
    testMath(std::string serverName, long port, int iterations);
    void run() override;
};


#endif //RADIATIONTESTSRUNNER_TESTMATH_H
