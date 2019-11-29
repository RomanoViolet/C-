#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <ManipulateDataStream.hpp>
#include <TypeA.hpp>
#include <TypeB.hpp>
#include <TypeC.hpp>
#include <TypeD.hpp>
#include <TypeE.hpp>
#include <string>

// Tests the class ManipulateDataStream

// Tests whether  the allocated memory to interfaces is really on the stack
// TODO Remove the magic number 1000 for the size of the allocated memory

TEST(Test_ManipulateDataStream, TestMemoryAllocationToInterfaces) {
  ManipulateDataStream m;
  m.initialize();
  
  // The interfaces are laid down linearly in memory -- first, test whether the left end of the layout.
  EXPECT_TRUE(m.getAllocatedMemoryAddress() <= static_cast<void*>(m.getAddressOfAggregateInterface().start) 
              && static_cast<char*>(m.getAllocatedMemoryAddress()) + 1000U >= static_cast<char*>(m.getAddressOfAggregateInterface().start)
              );

  // The interfaces are laid down linearly in memory -- first, test whether the right end of the layout.
  EXPECT_TRUE(m.getAllocatedMemoryAddress() <= static_cast<void*>(m.getAddressOfAggregateInterface().end) 
              && static_cast<char*>(m.getAllocatedMemoryAddress()) + 1000U >= static_cast<char*>(m.getAddressOfAggregateInterface().end)
              );
  
}

