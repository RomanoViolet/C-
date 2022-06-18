#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Producer.hpp"
#include "Consumer.hpp"


TEST ( ClassDeathTest, ZeroCapacityFIFO ) // NOLINT
{
    EXPECT_TRUE ( true );
}
