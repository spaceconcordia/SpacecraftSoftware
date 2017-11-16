#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int test = 0;
    int *p = &test;
    //int **pp = &p;

    printf("the address of test is: %p\nthe value of test pointer is: %d\n\n", (void*)&test, *p);

    // convert address to char string
    char *address_p = (void*)&test;
    printf("setting test = 1\n\n");
    test = 1;
    printf("the address of test is: %p\nthe value of test pointer is: %d\n\n\n", (void*)&test, *p);

/*
The C standard permits you to cast
an address of memory that you own to an unsigned char*:

unsigned char* p = (unsigned_char*)someaddress;

You can then extract the memory one byte at a time
using pointer arithmetic on p. Be careful not to go
beyond the memory that you own - bear in mind that
and int could be as small as 16 bits.*/



    // creating an array of the exact size we want (1MB to start, actually we want 64MB)
    int *data;

    printf("sizeof(int) == 4 -> %d\n", (sizeof(int) == 4));
    printf("sizeof(int) -> %ld\n\n", sizeof(int));
    printf("data address: L%p\n\n", (void*)&data);

    int val2 = 1;
    int val3 = 2;
    int val4 = 128;
    int *p2 = &val2;
    int *p3 = &val3;
    int *p4 = &val4;
    unsigned char *bytep1 = (unsigned char*)p; // int val of 1
    unsigned char *bytep2 = (unsigned char*)p2; // int val of 1
    unsigned char *bytep3 = (unsigned char*)p3; // int val of 2
    unsigned char *bytep4 = (unsigned char*)p4; // int val of 128

    //@TODO test increments of 4 of the value of byteps
    for (int i = 0; i < 32; i++) {
        printf("bytep1[%d]: %d\tbytep2[%d]: %d\tbytep3[%d]: %d\tbytep4[%d]: %d\n", i, bytep1[i], i, bytep2[i], i, bytep3[i], i, bytep4[i]);
        //printf("bytep[0]: %d\nbytep[1]: %d\n");

        // ((2^7)-1) 255 seems to be the max value I'm seeing...
        if (bytep1[i] == 255) { //@TODO do the same for the rest, but break it up the above printf statement into 4 different ones for that.
                                // i.e. handle it case by case
            printf(" <-- found 255!!! ");
        }
    }

    /*int bytes = (1024);
    data = (int *) malloc(bytes);

    for (int i = 0; i < bytes; i++) {
        data[i] = rand();
        printf("%d", data[i]);

        if (i < bytes - 1) {
            printf(",");
        }
    }
    printf("\n\nDone.");

    free(data);
    */
    return 0;
}
