#!/bin/sh

g++ -std=c++11 -pthread /home/alarm/RadiationTestsRunner/src/testrunner/*.cpp /home/alarm/RadiationTestsRunner/src/common/*.cpp -Itestrunner -Icommon -o /home/alarm/RadiationTestsRunner/src/radsrunner
