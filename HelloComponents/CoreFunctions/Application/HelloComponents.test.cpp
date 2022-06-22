#include "ComponentTypes/SharedMemoryConnect.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
TEST( BaseTests, Instantiation )  // NOLINT
{
  Producer p;
  Consumer c;
  SharedMemoryConnect< int16_t > shm;
  shm.from( p.a_out.toPtr( ) ).to( c.a_in.toPtr( ) );
  // c.a_in.setValue( 56U );
  // c.a_in.setValue( p.a_out.getValue( ) );
  // int16_t r = c.a_in.getValue( );
  // EXPECT_EQ( r, 45U );
  EXPECT_TRUE( true );
}
