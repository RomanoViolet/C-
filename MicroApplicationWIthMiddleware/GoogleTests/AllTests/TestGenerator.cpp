#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <GenerateDataStream.hpp>
#include <TypeA.hpp>
#include <TypeB.hpp>
#include <TypeC.hpp>
#include <string>

// Tests the class GenerateDataStream

// Tests whether  the allocated memory to interfaces is really on the stack
TEST(Test_GenerateDataStream, TestMemoryAllocationToInterfaces) {
  GenerateDataStream g;
  g.initialize();
  
  // The interfaces are laid down linearly in memory -- first, test whether the left end of the layout.
  EXPECT_TRUE(g.getAllocatedMemoryAddress() <= static_cast<void*>(g.getAddressOfAggregateInterface().start) 
              && static_cast<char*>(g.getAllocatedMemoryAddress()) + 1000U >= static_cast<char*>(g.getAddressOfAggregateInterface().start)
              );

  // The interfaces are laid down linearly in memory -- first, test whether the right end of the layout.
  EXPECT_TRUE(g.getAllocatedMemoryAddress() <= static_cast<void*>(g.getAddressOfAggregateInterface().end) 
              && static_cast<char*>(g.getAllocatedMemoryAddress()) + 1000U >= static_cast<char*>(g.getAddressOfAggregateInterface().end)
              );
  
}

// Tests whether the computation is as expected.
TEST(Test_GenerateDataStream, TestCompute) {
  // Tests whether  the allocated memory to interfaces is really on the stack
  GenerateDataStream g;
  g.initialize();

  // Test it for 100 times.
  double seedOutputStream_1 = -5;
  int outputStream_1_m2 = -1;
  double outputStream_2_m3 = 0;
  std::string outputStream_2_m4 = "Header";
  double outputStream_3_m3 = 1;
  char seedLetter = 'A';
  for (size_t i = 0; i < 100; ++i)
  {
    g.compute();

    // outputStream_1
    // -5, -4, ..., 0, 1, ...20, -5, -4, ..., 0, 1, ... 20, -5, ...
    EXPECT_DOUBLE_EQ(g.outputStream_1.m1, seedOutputStream_1);
    seedOutputStream_1++;
    seedOutputStream_1 = (seedOutputStream_1 > 20) ? -5 : seedOutputStream_1;

    // -1, 1, -1, 1, ...
    EXPECT_EQ(g.outputStream_1.m2, outputStream_1_m2);
    outputStream_1_m2 = (outputStream_1_m2 == 1) ? -1 : 1;

    // outputStream_2
    // Even positive integers: 0, 2, 4, 6, ....
    EXPECT_DOUBLE_EQ(g.outputStream_2.m3, outputStream_2_m3);
    outputStream_2_m3 = outputStream_2_m3 + 2;

    // Header, Body, Header, Body, ...
    EXPECT_EQ(g.outputStream_2.m4, outputStream_2_m4);
    outputStream_2_m4 = (outputStream_2_m4.compare("Header") == 0) ? "Body" : "Header";

    // Odd positive integers: 1, 3, 5, 7, ... 51, 1, 3, 5, ...
    EXPECT_DOUBLE_EQ(g.outputStream_3.m3, outputStream_3_m3);
    outputStream_3_m3 = outputStream_3_m3 + 2;
    outputStream_3_m3 = (outputStream_3_m3 > 51) ? 1U : outputStream_3_m3;
    
    EXPECT_EQ(g.outputStream_3.m4, std::string(1, seedLetter));  
    if (seedLetter <= 'Z' )
    {
      seedLetter = static_cast<char>(static_cast<int>(seedLetter) + 1);
    }
    else
    {
      seedLetter = 'A';
    }
    

  }
  
}

// Tests the filter method as provided by each interface class (e.g., TypeA, TypeB, ...) itself.
// The filters tested here are a proxy for housekeeping functions typically seen when an application binds to a middleware.
TEST(Test_GenerateDataStream, TestInterfaceProvidedFilters) 
{
  
  GenerateDataStream g;
  g.initialize();
  // Test it for 100 times.
  for (size_t i = 0; i < 100; ++i)
  {
    g.compute();

    double outputStream_2_m3_beforeFilter = g.outputStream_2.m3;
    std::string outputStream_2_m4_beforeFilter = g.outputStream_2.m4;
    double outputStream_3_m3_beforeFilter = g.outputStream_3.m3;

    g.filter();

    // assertion on output stream 1 of TypeA
    // m1 is limited to a maximum value of [-10, 10]
    EXPECT_LE(g.outputStream_1.m1, 10);
    EXPECT_GE(g.outputStream_1.m1, -10);

    // m2 takes binary values {0, 1}
    EXPECT_TRUE((g.outputStream_1.m2 == 0) || (g.outputStream_1.m2 ==1));

    // assertion on output stream 2 of TypeB
    // m3 is doubled.
    EXPECT_DOUBLE_EQ(g.outputStream_2.m3, 2*outputStream_2_m3_beforeFilter);

    // m4's text is changed. if "Header" -> "CompressedHeader"
    if (outputStream_2_m4_beforeFilter.compare("Header") == 0)
    {
      // expect "CompressedHeader"
      EXPECT_EQ("CompressedHeader", g.outputStream_2.m4);
    }
    else
    {
      // the string is m4 remains unchanged
      EXPECT_EQ("Header", g.outputStream_2.m4);
    }
    

    // assertion on output stream 3 of TypeC
    // m3 is limited to [7, 15]
    if (outputStream_3_m3_beforeFilter < 7)
    {
      EXPECT_DOUBLE_EQ(g.outputStream_3.m3, 7);
    }
    else if (outputStream_3_m3_beforeFilter > 15)
    {
      EXPECT_DOUBLE_EQ(g.outputStream_3.m3, 15);
    }
    else
    {
      EXPECT_DOUBLE_EQ(g.outputStream_3.m3, outputStream_3_m3_beforeFilter);
    }
    
    // outputStream_3.m4 is not modified.

  }

}