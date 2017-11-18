//
// Created by pbrink on 15/11/17.
//

#include "testMath.h"
#include "../common/testingparams.h"

void testMath::run() {
    sendMsg("Starting math test.");
    std::cout << "Starting math test." << std::endl;

    time_t startTest = time(0);
    time_t endTest = startTest + secondsToRun;
    while (time(0) < endTest) {
        // do the matrix calculation
        multiplyMatrices();
        verifyMatrix();
        resetResultMatrix();
    }

}

void testMath::multiplyMatrices() {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void testMath::verifyMatrix() {
    int errorCount = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (matrixC[i][j] != matrixSize) {
                errorCount++;
            }
        }
    }

    sendMsg("Errors: " + to_string(errorCount) + "/" + to_string(matrixSize*matrixSize));
    std::cout << ("Math test errors: " + to_string(errorCount)) << std::endl;
}

testMath::testMath(std::string testName, std::string serverName, long port) :
        task(testName, serverName, port) {
    secondsToRun = testingParams::numberOfMinutesToRun*60;
    // setup the matrices
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixA[i][j] = 1;
            matrixB[i][j] = 1;
            matrixC[i][j] = 0;
        }
    }
}

void testMath::resetResultMatrix() {
    // setup the matrices
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixC[i][j] = 0;
        }
    }
}
