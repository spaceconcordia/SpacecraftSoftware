//
// Created by pbrink on 15/11/17.
//

#include "listener.h"

void listener::runTask() {
    std::cout << "listener " << testName << " started." << std::endl;
//    pthread_t msg;
//    tcp.setup(port);
//    if(pthread_create(&msg, NULL, getMessages, (void *) 0) == 0)
//    {
//        tcp.receive();
//    }

    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                ssize_t len;
                char line[512];
                while ((len = stream->receive(line, sizeof(line))) > 0) {
                    line[len] = 0;
                    printf("received - %s\n", line);
                    logger->debug(line);
                    //logger->flush();
                    //stream->send(line, len);
                }
                delete stream;
            }
        }
    }
    exit(0);
}

//void listener::logMessage(string msg) {
//    std::string delim = "|";
//
//    auto start = 0U;
//    auto end = msg.find(delim);
//    while (end != std::string::npos)
//    {
//        std::cout << msg.substr(start, end - start) << std::endl;
//        start = end + delim.length();
//        end = msg.find(delim, start);
//    }
//
//    std::cout << msg.substr(start, end);
//}
//
//void * listener::getMessages(void *m)
//{
//    pthread_detach(pthread_self());
//    while(1)
//    {
//        string str = tcp.getMessage();
//        if( str != "" )
//        {
////            cout << "Message:" << str << endl;
//            //logMessage(str);
//            logger->info(str);
//            //tcp.Send("ciao paperino");
//            tcp.clean();
//        }
//        usleep(10);
//    }
//    tcp.detach();
//}