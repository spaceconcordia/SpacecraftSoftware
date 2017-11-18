//
// Created by pbrink on 15/11/17.
//

#include "task.h"

void task::sendMsg(std::string msg) {
    if (connector == NULL) {
        connector = new TCPConnector();
    }
    TCPStream* stream = connector->connect(serverName.c_str(), port);
    if (stream) {
        // get the current time
        time_t rawtime;
        time (&rawtime);
        std::string newMessage = ctime(&rawtime);
        // ctime adds a newline at the end of its string, so remove that
        size_t end = newMessage.find_last_of('\n');
        newMessage = newMessage.substr(0,end);
        // add the source and the actual message wanted
        newMessage.append(", " + testName + ", " + msg);
        // send to the server
        stream->send(newMessage.c_str(), newMessage.size());
        delete stream;
    }
}