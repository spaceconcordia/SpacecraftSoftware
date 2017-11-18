//
// Created by pbrink on 15/11/17.
//

#ifndef RADIATIONTESTSRUNNER_TESTPARAMS_H
#define RADIATIONTESTSRUNNER_TESTPARAMS_H

#include <iostream>
#include <vector>

namespace testingParams {

    static const int numberOfMinutesToRun = 1;

    static const std::pair<std::string, long> memory("memory", 23425);
    static const std::pair<std::string, long> sd("sd", 23426);
    static const std::pair<std::string, long> math("math", 23427);
    static const std::pair<std::string, long> eeprom("eeprom", 23428);
    static const std::pair<std::string, long> temp("temp", 23429);

    static const std::pair<std::string, long> mainServer("main", 23424);

    static const std::vector<std::pair<std::string, long>> allTests = {
            memory, sd, math
    };

}
#endif //RADIATIONTESTSRUNNER_TESTPARAMS_H
