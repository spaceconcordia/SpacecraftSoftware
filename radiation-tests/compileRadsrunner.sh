#!/bin/sh

g++ -std=c++11 -pthread testrunner/*.cpp common/*.cpp -Itestrunner -Icommon -o radsrunner
