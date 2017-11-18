# Client and Server for the Radiation Tests

## Building

### Host/Server
Currently not using cross-tools, so compile the server on your host system as you normally would (you can use the included CMakeLists.txt)

To do this, `cmake` is required.

1. Go to folder with `CMakeLists.txt` (root project folder)
2. Enter `cmake -H. -Bbuild` to generate cmake 
3. Enter `cmake --build build -- -j3` to build the project
4. Server executable will be located in the `build` subdirectory, and can be run directly from there

### Target/Client
To build on ARM, copy `src/common` and `src/testrunner` to a folder in the home directory of target device. In the parent folder, build by using:

To do this, use `scp`:

1. Determine IP address of the target (as with SSH)
2. Copy the files, format is `scp source_file(s) user@ip_address:destination_folder`. Example:
  1. `scp testrunner/* alarm@10.0.0.1:/home/debian/RadiationTestsRunner/src/testrunner`
  2. `scp common/* debian@10.0.0.1:/home/debian/RadiationTestsRunner/src/common`
3. Verify that the files are present on the target

Build on the target. To do this:
1. Go to the `src` folder that contains `common` and `testrunner`.
2. Run `g++ -std=c++11 -pthread testrunner/*.cpp common/*.cpp -Itestrunner -Icommon -o radsrunner`

## Usage

### Host/Server
`./radsserver --output-dir|-o <log output directory>`

Example: `./radsserver -o /home/user_name/radiationTest`

The log output directory must already exist.

### Target/Client
`./radsrunner [--server <server name/ip>] [--secondsToRun <number of test secondsToRun>]`

Example: `./radsrunner --server 10.0.0.2 --iterations 5`

### Test Parameters
Default test parameters can be changed in `src/common/testingparams.h` This includes changing the test names, their ports, and the default amount of time that the tests should be run for in a single testing iteration. This file is shared between both host and test runner, so any changes made to the file should be done before copying to the target, or identical changes must be made on both the server and the target.

## Adding Tests

For an example, see `src/testrunner/testMath.cpp`.

Create a new class, and inherit from `task`. Do computation in the `run()` method. Report information back to the server with the `sendMsg(std::string msg)` method.

In `src/common/testingparams.h`, add/verify the name of your test and the port (the number immediately next to the name). The port must be unique. If you are adding a new test, add the new pair that you created to the `allTests` vector.

In `src/testrunner/radsrunner.cpp`, create a new logger and an instance of your test (look for the vector `tasks` to see all others already present). Add the instance of your newly created class to the vector `tasks`.

Add your newly created header and cpp files to `CLIENT_SOURCE_FILES` in `CMakeLists.txt`

Test with the server to ensure that data is being properly received.

Test on target device to ensure that test sizes are reasonable.
