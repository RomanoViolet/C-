#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CircularBuffer.hpp"

TEST ( ShouldCompile, Test1 )  // NOLINT
{
    GeneralClass< int > d ( 10 );
    EXPECT_TRUE ( true );
}

TEST ( ShouldNotCompile, Test1 )  // NOLINT
{
    GeneralClass< float > d ( 10 );
    EXPECT_TRUE ( true );
}
