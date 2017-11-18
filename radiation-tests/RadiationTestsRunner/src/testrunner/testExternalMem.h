#ifndef RADIATIONTESTSRUNNER_TESTRAM_H
#define RADIATIONTESTSRUNNER_TESTRAM_H


#include "task.h"

class testRAM : public task {

public:
    testRAM(std::string serverName, long port);
    void run() override;
};


#endif //RADIATIONTESTSRUNNER_TESTRAM_H
