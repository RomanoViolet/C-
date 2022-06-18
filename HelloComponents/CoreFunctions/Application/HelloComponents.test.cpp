#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Producer.hpp"
#include "Consumer.hpp"


TEST ( ClassDeathTest, ZeroCapacityFIFO ) // NOLINT
{
    Producer p;
    Consumer c;
    c.a_in.setValue(p.a_out.getValue());
    EXPECT_TRUE ( true );
}
