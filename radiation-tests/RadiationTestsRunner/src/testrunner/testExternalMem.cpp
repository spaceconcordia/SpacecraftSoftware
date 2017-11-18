#include "testExternalMem.h"
#include <iostream>
#include <fstream>

void testExternalMem::run() {
    sendMsg("Starting external memory test.");
    std::cout << "Starting external memory test." << std::endl;

    ofstream myfile;

    // 100 1MB text files of 0's at a time
    int charSize = sizeof(char); // in bytes
    int multiplier = 1024/charSize;
    int bytesToWrite = charSize * multiplier * 1024;
    int files = 100;
    int loops = 1;
    int timeLengthInMinutes = 1;

    printf("charSize = %d\nbytesToWrite = %d\n", charSize, bytesToWrite);

    // create test file directory
    const int dir_err = system("mkdir -p externalMemTestData");
    if (-1 == dir_err) {
        printf("Error creating directory!\n");
        sendMsg("ERROR CREATING DIRECTORY FOR EXTERNAL MEMORY TEST!");
        return;
    }

    // create files
    for (int i = 0; i < files; i++) {
        myfile.open("externalMemTestData/test" + std::to_string(i) + ".txt");
        for (int j = 0; j < bytesToWrite; j++) {
            myfile << "0";
        }

        myfile.close();
    }

    // check that all files are correct
    unsigned long filesCorrupted = 0;
    char ch;
    int duration = 60 * timeLengthInMinutes; // min test
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
        sendMsg("Errors: " + std::to_string(filesCorrupted) + " / " + std::to_string(files*loops));
    }

    printf("Finished test with %ld files corrupted out of %d\n", filesCorrupted, (files*loops));

    const int delete_err = system("rm -rf externalMemTestData");
    if (0 != delete_err) {
        printf("Error deleting directory!\n");
        exit(1);
    }
}

testExternalMem::testExternalMem(std::string serverName, long port) : task(serverName, port) {

}

