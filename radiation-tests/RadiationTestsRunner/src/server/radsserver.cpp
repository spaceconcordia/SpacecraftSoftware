#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include "listener.h"
#include "../common/testingparams.h"
#include "../../libs/spdlog/spdlog.h"

int main(int argc, char *argv[]){
    std::string outputDirectory;

    // set test parameters from command line
    bool unknownArgument = false;
    if (argc > 1) {
        for (int i = 1; i < argc - 1; i++) {
            if ((std::strcmp(argv[i], "--output-dir") == 0) || (std::strcmp(argv[i], "-o") == 0)) {
                outputDirectory = argv[++i];
            } else {
                unknownArgument = true;
            }
        }
    }
    if (outputDirectory.empty()) {
        std::cout << "No output directory supplied." << std::endl;
        unknownArgument = true;
    }
    if (unknownArgument) {
        std::cout << "Unknown arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << " --output-dir|-o <output directory>" << std::endl;
        return 1;
    }
    std::cout << "Will place all output files in " << outputDirectory << std::endl;

    // setup loggers
    size_t q_size = 4096; //queue size must be power of 2
    spdlog::set_async_mode(q_size, spdlog::async_overflow_policy::block_retry, nullptr, std::chrono::seconds(2));
    spdlog::set_level(spdlog::level::debug);

    // create server listener threads
    std::vector<listener*> listeners;
    for (std::pair<std::string, long> test : testingParams::allTests) {
        auto logger = spdlog::basic_logger_mt(test.first, outputDirectory + "/" + test.first + ".log");
        listeners.push_back(new listener(test.first, outputDirectory, test.second, logger));
    }
    // create the logger and listener for the main server
    //auto mainServerLogger = spdlog::basic_logger_mt(testingParams::mainServer.first, outputDirectory + "/" +
    //        testingParams::mainServer.first + ".log");
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    std::string mainServerLogPath = outputDirectory + "/" + testingParams::mainServer.first + ".log";
    sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_mt>(mainServerLogPath));
    auto mainServerLogger = std::make_shared<spdlog::logger>(testingParams::mainServer.first, begin(sinks), end(sinks));
    spdlog::register_logger(mainServerLogger);
    mainServerLogger->flush_on(spdlog::level::info);
    listeners.push_back(new listener(testingParams::mainServer.first, outputDirectory, testingParams::mainServer.second,
                                     mainServerLogger));

    // start listener threads
    std::thread listenerThreads[listeners.size()];
    for (int i = 0; i < listeners.size(); i++) {
        listenerThreads[i] = std::thread(&listener::runTask, listeners[i]);
    }
    mainServerLogger->info("Started listeners");

    // wait for all listeners to finish (actually never)
    for (int i = 0; i < listeners.size(); i++) {
        listenerThreads[i].join();
    }


    return 0;

}
