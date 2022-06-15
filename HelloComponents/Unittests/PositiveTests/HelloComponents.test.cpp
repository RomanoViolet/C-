#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "Application/Producer.hpp"
#include "Application/Consumer.hpp"


TEST ( ClassDeathTest, ZeroCapacityFIFO ) // NOLINT
{
    EXPECT_TRUE ( true );
}
