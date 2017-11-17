#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {
    unsigned long bytes = (64*1024*1024); // 64 MB
    unsigned long volatile *data = (unsigned long *) malloc(sizeof(unsigned long) * bytes);
    unsigned long testDuration = 0;
    unsigned long bitFlipsCtr = 0;

    printf("how long do you want this test to go on for? (in min): ");

    scanf("%ld", &testDuration);

    testDuration = testDuration * 60; // convert to seconds

    printf("\ninitializing 64 MB size array of integers, setting all values to 0...\n");

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

    free((void*)data);

    return 0;
}
