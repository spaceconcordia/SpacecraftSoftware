//
// Created by pbrink on 15/11/17.
//

#ifndef RADIATIONTESTSRUNNER_TASK_H
#define RADIATIONTESTSRUNNER_TASK_H

#include <iostream>
#include "tcpconnector.h"

class task {
protected:
    std::string testName;
    std::string logDirectory;
    std::string serverName;
    long port;
    TCPConnector* connector;
    void sendMsg(std::string msg);
    void sendToFile(const string &fileName, const string &content, bool append);
public:
    task(std::string testName, std::string logDirectory, std::string serverName, long port) :
            testName(testName), logDirectory(logDirectory), serverName(serverName), port(port) {}
    virtual void run() {};
};


#endif //RADIATIONTESTSRUNNER_TASK_H
