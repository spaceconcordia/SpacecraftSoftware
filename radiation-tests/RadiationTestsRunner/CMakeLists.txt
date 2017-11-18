cmake_minimum_required(VERSION 3.8)
project(RadiationTestsRunner)

set(CMAKE_CXX_STANDARD 11)

find_package( Threads )

set(CLIENT_SOURCE_FILES src/testrunner/radsrunner.cpp src/testrunner/tcpconnector.cpp src/testrunner/tcpconnector.h src/common/tcpstream.cpp src/common/tcpstream.h src/testrunner/task.cpp src/testrunner/task.h src/common/testingparams.h src/testrunner/taskMath.cpp src/testrunner/taskMath.h src/testrunner/testRAM.cpp src/testrunner/testRAM.h src/testrunner/Checksum.h src/testrunner/Checksum.cpp)
set(SERVER_SOURCE_FILES src/server/radsserver.cpp src/server/listener.cpp src/server/listener.h src/server/tcpacceptor.cpp src/server/tcpacceptor.h src/common/tcpstream.cpp src/common/tcpstream.h src/common/testingparams.h)

add_library(spdlog STATIC "${CMAKE_SOURCE_DIR}/libs/spdlog")
set_target_properties(spdlog PROPERTIES LINKER_LANGUAGE CXX)

add_executable(RadiationTestsClient ${CLIENT_SOURCE_FILES})
add_executable(RadiationTestsServer ${SERVER_SOURCE_FILES})

target_link_libraries( RadiationTestsClient ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( RadiationTestsServer ${CMAKE_THREAD_LIBS_INIT} spdlog )
