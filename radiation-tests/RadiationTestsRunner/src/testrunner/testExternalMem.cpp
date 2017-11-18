#include "testExternalMem.h"
#include <iostream>
#include <fstream>

void testRAM::run() {
    sendMsg("Starting external memory test.");
    std::cout << "Starting external memory test." << std::endl;

    ofstream myfile;

    // 1MB, 10

    int i = 0;
    while (i < 10) {
        myfile.open("~/sampleData/test." + std::to_string(i) + "txt");
    }




/*-------------------------------------------------------------------------------------------------*/
    unsigned long bytes = (64*1024*1024); // 64 MB
    unsigned long volatile *data = (unsigned long *) malloc(sizeof(unsigned long) * bytes);
    unsigned long testDuration = 5; // 5 min default
    unsigned long bitFlipsCtr = 0;

    // printf("how long do you want this test to go on for? (in min): ");

    // scanf("%ld", &testDuration);

    testDuration = testDuration * 60; // convert to seconds

    printf("\ninitializing 64 MB size array of integers, setting all values to 0\n");

    for (unsigned long i = 0; i < bytes; i++) {
        data[i] = 0;
    }

    printf("checking for bitflips now\n");

    time_t startTest = time(0); // get the system time
    time_t endTest = startTest + testDuration;

    while (time(0) < endTest) {
        for (unsigned long i = 0; i < bytes; i++) {
            if (data[i] != 0) {
                data[i] = 0; // reset to 0
                bitFlipsCtr++;
            }
        }
    }

    printf("\nFinished test with %ld bit flip(s) detected\n", bitFlipsCtr);
    sendMsg("Finished test with " + std::to_string(bitFlipsCtr) + " bit flips for " + std::to_string(bytes*8) + " bits checked");

    free((void*)data);
}

testRAM::testRAM(std::string serverName, long port) : task(serverName, port) {

}

