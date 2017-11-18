#include <iostream>
#include <cstring>
#include <thread>
#include <sys/stat.h>
#include <dirent.h>
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
    std::string logDirectory = "../logs";
    int numIterations;

    // set test parameters from command line
    bool unknownArgument = false;
	if (argc > 1) {
        for (int i = 1; i < argc - 1; i++) {
            if (std::strcmp(argv[i], "--server") == 0) {
                serverAddress = argv[++i];
            } else if (std::strcmp(argv[i], "--iterations") == 0) {
                numIterationsString = argv[++i];
            } else if (std::strcmp(argv[i], "--output-directory") == 0 || std::strcmp(argv[i], "-o") == 0) {
                logDirectory = argv[++i];
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

    // create local log directory
    if (!logDirectory.empty()) {
        DIR* dir;
        dir = opendir(logDirectory.c_str());
        if (dir != NULL) {
            closedir(dir);
        } else {
            const int dir_err = mkdir(logDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (-1 == dir_err)
            {
                std::cout << "Error creating directory at " << logDirectory << std::endl;
                exit(1);
            }
        }
    } else {
        unknownArgument = true;
    }

    if (unknownArgument) {
        std::cout << "Unknown arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << " [--server <server name/ip>] [--secondsToRun <number of test secondsToRun>]" << std::endl;
        return 1;
    }

    // create local log directory
    if (!logDirectory.empty()) {
        DIR* dir;
        dir = opendir(logDirectory.c_str());
        if (dir != NULL) {
            closedir(dir);
        } else {
            const int dir_err = mkdir(logDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (-1 == dir_err)
            {
                std::cout << "Error creating directory at " << logDirectory << std::endl;
                exit(1);
            }
        }
    }


    std::cout << "Using server " << serverAddress << std::endl;
    std::cout << "Will repeat all all tests " << numIterations << " times." << std::endl;


    // establish tcp connection
    TCPConnector* connector = new TCPConnector();

    // setup all tests
    std::vector<task*> tasks;
    tasks.push_back(new testMath(testingParams::math.first, logDirectory, serverAddress, testingParams::math.second));
    tasks.push_back(new testRAM(testingParams::memory.first, logDirectory, serverAddress, testingParams::memory.second));
    tasks.push_back(new testExternalMem(testingParams::sd.first, logDirectory, serverAddress, testingParams::sd.second));

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
