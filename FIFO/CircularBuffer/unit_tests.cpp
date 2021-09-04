#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
TEST ( ShouldCompile, ZeroCapacityFIFO ) // NOLINT
{
    //CircularBuffer< int, 0U > f;
    static_assert ( ! NonZeroCapacityOfBuffer< int, 0 > );
    EXPECT_TRUE ( true );
    // https://godbolt.org/z/5z19b74oz
    ASSERT_DEATH_IF_SUPPORTED (
        {
            CircularBuffer< int, 0 > b { };
            ( void ) b;
        },
        "error:" );
}
