#include <iostream>
#include <cstring>
#include <thread>
#include "../common/tcpstream.h"
#include "../common/testingparams.h"
#include "tcpconnector.h"
#include "task.h"
#include "testMath.h"
#include "testRAM.h"
#include "testExternalMem.h"

void notifyMainServer(const string &serverAddress, TCPConnector *connector, std::string message) {
    TCPStream* stream = connector->connect(serverAddress.c_str(), testingParams::mainServer.second);
    if (stream) {
        stream->send(message.c_str(), message.size());
        delete stream;
    }
}

int main(int argc, char *argv[]){
	std::string serverAddress = "192.168.1.139";
    std::string numIterationsString = "1";
    int numIterations;

    // set test parameters from command line
    bool unknownArgument = false;
	if (argc > 1) {
        for (int i = 1; i < argc - 1; i++) {
            if (std::strcmp(argv[i], "--server") == 0) {
                serverAddress = argv[++i];
            } else if (std::strcmp(argv[i], "--iterations") == 0) {
                numIterationsString = argv[++i];
            } else {
                unknownArgument = true;
            }
        }
    }
    try {
        numIterations = stoi(numIterationsString);
    } catch (std::exception const & e) {
        unknownArgument = true;
    }
    if (unknownArgument) {
        std::cout << "Unknown arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << " [--server <server name/ip>] [--iterations <number of test iterations>]" << std::endl;
        return 1;
    }
    std::cout << "Using server " << serverAddress << std::endl;
    std::cout << "Will repeat all all tests " << numIterations << " times." << std::endl;


    // establish tcp connection
    TCPConnector* connector = new TCPConnector();

    // setup all tests
    std::vector<task*> tasks;
    tasks.push_back(new testMath(serverAddress, testingParams::math.second, 5));
    tasks.push_back(new testRAM(serverAddress, testingParams::memory.second));
    tasks.push_back(new testExternalMem(serverAddress, testingParams::sd.second));

    // run all tests the specified number of times
    for (int iterationNumber = 1; iterationNumber <= numIterations; iterationNumber++) {
        // start the tests
        std::thread taskThreads[tasks.size()];
        for (int i = 0; i < tasks.size(); i++) {
            taskThreads[i] = std::thread(&task::run, tasks[i]);
        }
        notifyMainServer(serverAddress, connector, "Task round " + std::to_string(iterationNumber) + " started.");

        // wait for the tests to finish
        for (int i = 0; i < tasks.size(); i++) {
            taskThreads[i].join();
        }
        notifyMainServer(serverAddress, connector, "Task round " + std::to_string(iterationNumber) + " finished.");
    }

    notifyMainServer(serverAddress, connector, "All tasks finished.");

    return 0;
}
