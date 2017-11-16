# Client and Server for the Radiation Tests

## Building

### Host/Server
Currently not using cross-tools, so compile the server on your host system as you normally would (you can use the included CMakeLists.txt)

### Target/Client
To build on ARM, copy `src/common` and `src/testrunner` to a folder in the home directory of target device. In the parent folder, build by using:

`g++ -std=c++11 -pthread testrunner/*.cpp common/*.cpp -Itestrunner -Icommon -o radsrunner`

## Usage

### Host/Server
`./radsserver --output-dir|-o <log output directory>`

### Target/Client
`./radsrunner [--server <server name/ip>] [--iterations <number of test iterations>]`

## Adding Tests

For an example, see `src/taskMath.cpp`.

Create a new class, and inherit from `task`. Do computation in the `run()` method. Report information back to the server with the `sendMsg(std::string msg)` method.

In `common/testingParams.h`, add/verify the name of your test and the port (the number immediately next to the name). The port must be unique. If you are adding a new test, add the new pair that you created to the `allTests` vector.

In `radsrunner.cpp`, add the instance of your newly created class to the vector `tasks`.

Test with the server to ensure that data is being properly received.
