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
        time_t rawtime;
        time (&rawtime);
        std::string newMessage = ctime(&rawtime);
        newMessage.append(" " + msg);
        stream->send(newMessage.c_str(), newMessage.size());
        delete stream;
    }
}