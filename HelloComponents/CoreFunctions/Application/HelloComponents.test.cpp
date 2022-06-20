#include "Consumer.hpp"
#include "Producer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST( BaseTests, Instantiation )  // NOLINT
{
  Producer p;
  Consumer c;
  c.a_in.setValue( 56U );
  c.a_in.setValue( p.a_out.getValue( ) );
  int16_t r = c.a_in.getValue( );
  EXPECT_EQ( r, 45U );
}
