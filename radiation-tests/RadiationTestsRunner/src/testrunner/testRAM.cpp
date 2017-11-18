#include "testRAM.h"
#include "../common/testingparams.h"
#include <stdlib.h>


void testRAM::run() {
    sendMsg("Starting RAM test.");
    std::cout << "Starting RAM test." << std::endl;

    unsigned long bytes = (64*1024*1024); // 64 MB
    unsigned long volatile *data = (unsigned long *) malloc(sizeof(unsigned long) * bytes);
    unsigned long testDuration = testingParams::numberOfMinutesToRun;
    unsigned long bitFlipsCtr = 0;

    testDuration = testDuration * 60; // convert to seconds

    printf("\nInitializing 64 MB size array of integers, setting all values to 0\n");
    sendMsg("Initializing 64 MB size array of integers, setting all values to 0");

    for (unsigned long i = 0; i < bytes; i++) {
        data[i] = 0;
    }

    printf("checking for bitflips now\n");

    time_t startTest = time(0); // get the system time
    time_t endTest = startTest + testDuration;

    long numLoops = 0;
    while (time(0) < endTest) {
        for (unsigned long i = 0; i < bytes; i++) {
            if (data[i] != 0) {
                data[i] = 0; // reset to 0
                bitFlipsCtr++;
            }
        }
        numLoops++;
        sendMsg("Errors: " + std::to_string(bitFlipsCtr) + " bits / " + std::to_string(64 * numLoops) + " MB");
    }

    printf("\nFinished memory test with %ld bit flip(s) detected\n", bitFlipsCtr);
    sendMsg("Finished memory test with " + std::to_string(bitFlipsCtr) + " bits in error / " + std::to_string(64 * numLoops) + " MB.");

    free((void*)data);
}

testRAM::testRAM(std::string testName, std::string logDirectory, std::string serverName, long port) :
        task(testName, logDirectory, serverName, port) {

}

