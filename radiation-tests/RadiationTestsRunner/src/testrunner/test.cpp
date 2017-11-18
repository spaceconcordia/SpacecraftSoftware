#include "testExternalMem.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

int main() {
    // sendMsg("Starting external memory test.");
    std::cout << "Starting external memory test." << std::endl;

    ofstream myfile;

    // 100 1MB text files of 0's at a time
    int charSize = sizeof(char); // in bytes
    int multiplier = 1024/charSize;
    int bytesToWrite = charSize * multiplier * 1024;
    int files = 100;
    int loops = 1;
    
    printf("charSize = %d\nbytesToWrite = %d\n", charSize, bytesToWrite);

    const int dir_err = system("mkdir -p externalMemTestData");
    if (-1 == dir_err) {
        printf("Error creating directory!\n");
        exit(1);
    }

    for (int i = 0; i < files; i++) {
        myfile.open("externalMemTestData/test" + std::to_string(i) + ".txt");
        
        if (i == 0) {
            // create checksum to check against only once, since it will be the same
        }
        // each text file will be a little over 1024 KB
        for (int j = 0; j < bytesToWrite; j++) {
            myfile << "0";
        }

        myfile.close();
    }

    unsigned long filesCorrupted = 0;
    char ch;
    int duration = 60 * 5; // min test
    time_t startTest = time(0);
    time_t endTest = startTest + duration;
    
    while (time(0) < endTest) {
        for (int i = 0; i < files; i++) {
            fstream fin("externalMemTestData/test" + std::to_string(i) + ".txt", fstream::in);
            while (fin >> noskipws >> ch) { // noskipws -> no skip white spaces
                if (ch != '0') {
                    filesCorrupted++;
                    break;
                }
            }
        }
        loops++;
    }

    printf("Finished test with %ld files corrupted out of %d\n", filesCorrupted, (files*loops));

    const int delete_err = system("rm -rf externalMemTestData");
    if (0 != delete_err) {
        printf("Error creating directory!\n");
        exit(1);
    }

    return 0;
}

