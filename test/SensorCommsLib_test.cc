#include "gtest/gtest.h"
#include "SensorCommsLib/Sensor.h"
#include "SensorCommsLib/SampleSensor.h"

#include <vector>
#include <string>

class SensorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // any actions that should be run before every test
    }

    // virtual void TearDown() {} // any actions that should be run after every test

    std::string testInputFIFO = "/tmp/testInput";
    std::string testOutputFIFO = "/tmp/testOutput";

    // SampleSensor readWriteSensor = SampleSensor("ReadWriteSensor", "address", 1000, ReadWrite::READ_WRITE, testInputFIFO, testOutputFIFO);
    SampleSensor writeSensor = SampleSensor("WriteSensor", "address", 1000, ReadWrite::WRITE, testInputFIFO, "");
    SampleSensor readSensor = SampleSensor("ReadSensor", "address", 1000, ReadWrite::READ, "", testInputFIFO);
};

TEST_F(SensorTest, WriteThenReadFromPipe) {
    std::string originalString = "A string to test!";
    readSensor.readFrom();
    std::string receivedFromInput = writeSensor.receiveFromInput();
    EXPECT_EQ(originalString, receivedFromInput);
}

// TEST_F(SensorTest, ReadWriteFromPipe) {
//     std::string originalString = "A string to test!";
//     readSensor.readFrom();
//     std::string readFromFifo = writeSensor.receiveFromInput();
//     testing::internal::CaptureStdout();
    
//     writeSensor.writeTo(data);
//     std::string output = testing::internal::GetCapturedStdout();
//     EXPECT_EQ(data, output); 
// }
// TEST_F(SensorTest, DequeueWorks) {
//     int* n = q0_.Dequeue();
//     EXPECT_EQ(NULL, n);

//     n = q1_.Dequeue();
//     ASSERT_TRUE(n != NULL);
//     EXPECT_EQ(1, *n);
//     EXPECT_EQ(0, q1_.size());
//     delete n;

//     n = q2_.Dequeue();
//     ASSERT_TRUE(n != NULL);
//     EXPECT_EQ(2, *n);
//     EXPECT_EQ(1, q2_.size());
//     delete n;
// }