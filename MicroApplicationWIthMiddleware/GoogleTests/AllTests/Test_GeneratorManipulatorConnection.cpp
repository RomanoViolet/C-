#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <GenerateDataStream.hpp>
#include <ManipulateDataStream.hpp>
#include <string>

TEST(GeneratorManipulatorConnection, TestConnectivityWithFilters) {
    GenerateDataStream generator;
    ManipulateDataStream manipulator;
    
    generator.initialize();
    manipulator.initialize();

    // run the application for 100 cycles.
    for (int i = 0; i < 100; ++i)
    {
        generator.compute();

        double outputStream_2_m3_beforeFilter = generator.outputStream_2.m3;
        std::string outputStream_2_m4_beforeFilter = generator.outputStream_2.m4;
        double outputStream_3_m3_beforeFilter = generator.outputStream_3.m3;

        generator.filter();
        generator.outputStream_1.publishTo(manipulator.inputStream_1);
        generator.outputStream_2.publishTo(manipulator.inputStream_2);
        generator.outputStream_3.publishTo(manipulator.inputStream_3);

        // assertion on output stream 1 of TypeA
        // m1 is limited to a maximum value of [-10, 10]
        EXPECT_LE(manipulator.inputStream_1.m1, 10);
        EXPECT_GE(manipulator.inputStream_1.m1, -10);

        // m2 takes binary values {0, 1}
        EXPECT_TRUE((manipulator.inputStream_1.m2 == 0) || (manipulator.inputStream_1.m2 ==1));

        // assertion on output stream 2 of TypeB
        // m3 is doubled.
        EXPECT_DOUBLE_EQ(manipulator.inputStream_2.m3, 2*outputStream_2_m3_beforeFilter);

        // m4's text is changed. if "Header" -> "CompressedHeader"
        if (outputStream_2_m4_beforeFilter.compare("Header") == 0)
        {
        // expect "CompressedHeader"
        EXPECT_EQ("CompressedHeader", manipulator.inputStream_2.m4);
        }
        else
        {
        // the string is m4 remains unchanged
        EXPECT_EQ("Header", manipulator.inputStream_2.m4);
        }
        

        // assertion on output stream 3 of TypeC
        // m3 is limited to [7, 15]
        if (outputStream_3_m3_beforeFilter < 7)
        {
        EXPECT_DOUBLE_EQ(manipulator.inputStream_3.m3, 7);
        }
        else if (outputStream_3_m3_beforeFilter > 15)
        {
        EXPECT_DOUBLE_EQ(manipulator.inputStream_3.m3, 15);
        }
        else
        {
        EXPECT_DOUBLE_EQ(manipulator.inputStream_3.m3, outputStream_3_m3_beforeFilter);
        }
        
        // outputStream_3.m4 is not modified.


    }
    


    EXPECT_TRUE(true);
}