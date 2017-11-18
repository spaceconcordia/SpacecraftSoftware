#include "testExternalMem.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    // sendMsg("Starting external memory test.");
    std::cout << "Starting external memory test." << std::endl;

    ofstream myfile;

    // 100 1024KB text files
    int charSize = sizeof(char); // in bytes
    int multiplier = 1024/charSize;
    int bytesToWrite = charSize * multiplier * 1024;
    
    printf("charSize = %d\nbytesToWrite = %d\n", charSize, bytesToWrite);

    const int dir_err = system("mkdir -p externalMemTestData");
    if (-1 == dir_err) {
        printf("Error creating directory!\n");
        exit(1);
    }

    int i = 0;
    while (i < 100) {
        myfile.open("externalMemTestData/test" + std::to_string(i) + ".txt");
        
        // each text file will be a little over 1024 KB
        for (int j = 0; j < bytesToWrite; j++) {
            myfile << "0";
        }

        myfile.close();
        i++;
    }

    return 0;
}
