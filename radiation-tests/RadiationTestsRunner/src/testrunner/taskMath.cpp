//
// Created by pbrink on 15/11/17.
//

#include "taskMath.h"

void taskMath::run() {
    sendMsg("Starting math test.");
    std::cout << "Starting math test." << std::endl;

    for (int n = 0; n < iterations; n++) {
        // do the matrix calculation
        multiplyMatrices();
        verifyMatrix();
        resetResultMatrix();
    }

}

void taskMath::multiplyMatrices() {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void taskMath::verifyMatrix() {
    int errorCount = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (matrixC[i][j] != matrixSize) {
                errorCount++;
            }
        }
    }

    sendMsg("Errors: " + to_string(errorCount) + "/" + to_string(matrixSize*matrixSize));
    std::cout << ("Errors: " + to_string(errorCount)) << std::endl;
}

taskMath::taskMath(std::string serverName, long port, int iterations) : task(serverName, port),
                                                                        iterations(iterations){
    // setup the matrices
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixA[i][j] = 1;
            matrixB[i][j] = 1;
            matrixC[i][j] = 0;
        }
    }
}

void taskMath::resetResultMatrix() {
    // setup the matrices
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixC[i][j] = 0;
        }
    }
}
