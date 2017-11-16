//
// Created by pbrink on 15/11/17.
//

#ifndef RADIATIONTESTSRUNNER_LISTENER_H
#define RADIATIONTESTSRUNNER_LISTENER_H

#include <iostream>

//#include "libs/spdlog/spdlog.h"
#include "tcpacceptor.h"
#include "../../libs/spdlog/logger.h"

class listener {
private:
    std::string testName;
    std::string directory;
    std::shared_ptr<spdlog::logger> logger;
    long port;
    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
public:
    listener(std::string testName, std::string directory, long port, std::shared_ptr<spdlog::logger> logger)
            : testName(testName),
              directory(directory), port(port), logger(logger) {
        acceptor = new TCPAcceptor(port);
    }
    void runTask();
};


#endif //RADIATIONTESTSRUNNER_LISTENER_H
