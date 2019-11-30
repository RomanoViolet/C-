#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <GenerateDataStream.hpp>
#include <ManipulateDataStream.hpp>
#include <TypeA.hpp>
#include <TypeB.hpp>
#include <TypeC.hpp>
#include <TypeD.hpp>
#include <TypeE.hpp>
#include <string>

// Tests the customFilter class.

TEST(Test_CustomFilter, TestMemoryAllocationToInterfaces) {
  
  GenerateDataStream generator;
  ManipulateDataStream manipulator;
  manipulator.initialize();

  for (int i = 0; i < 100; ++i)
  {
    generator.compute();

    generator.outputStream_1.publishTo(manipulator.inputStream_1);
    generator.outputStream_2.publishTo(manipulator.inputStream_2);
    generator.outputStream_3.publishTo(manipulator.inputStream_3);

    // get data received by the manipulator before any filter is applied.
    // Due to the construction in Builder.inl, customFilter is only currently applied only to ports of type input.
    //double manipulator_inputStream_1_m1 = manipulator.inputStream_1.m1;
    //int manipulator_inputStream_1_m2 = manipulator.inputStream_1.m2;

    double manipulator_inputStream_2_m3 = manipulator.inputStream_2.m3;
    std::string manipulator_inputStream_2_m4 = manipulator.inputStream_2.m4;

    double manipulator_inputStream_3_m3 = manipulator.inputStream_3.m3;
    std::string manipulator_inputStream_3_m4 = manipulator.inputStream_3.m4;

    //manipulator.compute();

    // apply custom filter <NotMyApp> class of filters.
    manipulator.myCustomFilter();

    EXPECT_DOUBLE_EQ(13.5443, manipulator.inputStream_1.m1);
    EXPECT_EQ(12, manipulator.inputStream_1.m2);

    EXPECT_DOUBLE_EQ(manipulator_inputStream_2_m3/1.24, manipulator.inputStream_2.m3);
    EXPECT_EQ(manipulator_inputStream_2_m4 + ".. uh oh Not My App", manipulator.inputStream_2.m4);

    EXPECT_DOUBLE_EQ(manipulator_inputStream_3_m3 + 1.34, manipulator.inputStream_3.m3);
    EXPECT_EQ("oh oh " + manipulator_inputStream_3_m4, manipulator.inputStream_3.m4);

    
  }

}

