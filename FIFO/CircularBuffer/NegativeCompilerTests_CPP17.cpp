#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "TypeExists.hpp"

namespace cpp_17
{
    TEST(ShouldNotCompile, CircularBufferWithZeroCapacity)
    {
        cpp_17::CircularBuffer<int,0U> b{};
        (void)b;
    }
}

