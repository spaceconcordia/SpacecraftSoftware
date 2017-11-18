#ifndef RADIATIONTESTSRUNNER_TESTEXTERNALMEM_H
#define RADIATIONTESTSRUNNER_TESTEXTERNALMEM_H


#include "task.h"

class testExternalMem : public task {

public:
    testExternalMem(std::string serverName, long port);
    void run() override;
};


#endif //RADIATIONTESTSRUNNER_TESTEXTERNALMEM_H
