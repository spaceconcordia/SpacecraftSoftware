//
// Created by pbrink on 15/11/17.
//

#include "listener.h"

void listener::runTask() {
    std::cout << "Listener " << testName << " started." << std::endl;

    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                ssize_t len;
                char line[512];
                while ((len = stream->receive(line, sizeof(line))) > 0) {
                    line[len] = 0;
                    printf("%s\n", line);
                    logger->info(line);
                }
                delete stream;
            }
        }
    }
    exit(0);
}
