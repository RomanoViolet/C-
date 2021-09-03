#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST ( ShouldCompile, ZeroCapacityFIFO ) // NOLINT
{
    CircularBuffer< int, 0U > f;
    EXPECT_TRUE ( true );
}
