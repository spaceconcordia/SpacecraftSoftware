//
// Created by pbrink on 15/11/17.
//

#ifndef RADIATIONTESTSRUNNER_TESTMATH_H
#define RADIATIONTESTSRUNNER_TESTMATH_H


#include "task.h"

class testMath : public task {
private:
    int secondsToRun;
    const static int matrixSize = 500;
    int matrixA[matrixSize][matrixSize];
    int matrixB[matrixSize][matrixSize];
    int matrixC[matrixSize][matrixSize];
    void multiplyMatrices();
    void verifyMatrix();
    void resetResultMatrix();
public:
    testMath(std::string testName, std::string logDirectory, std::string serverName, long port);
    void run() override;
};


#endif //RADIATIONTESTSRUNNER_TESTMATH_H
