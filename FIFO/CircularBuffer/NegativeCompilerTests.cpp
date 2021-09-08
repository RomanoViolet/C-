#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "TypeExists.hpp"

namespace cpp20_concepts
{
    TEST ( ShouldNotCompile, CircularBufferWithZeroCapacity )  // NOLINT
    {
        CircularBuffer<int, 0> b{};
    }
} //namespace cpp20_concepts

