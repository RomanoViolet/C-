#include "ComponentTypes/SharedMemoryConnect.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#ifndef NDEBUG
TEST( BaseTests, Instantiation )  // NOLINT
{
  Producer p;
  Consumer c;
  SharedMemoryConnect< int16_t > shm;
  shm.from( p.a_out.toPtr( ) ).to( c.a_in.toPtr( ) );
  EXPECT_EQ( c.getStoredValue( ), 37U );

  // EXPECT_EQ( r, 45U );
  EXPECT_TRUE( true );
}
#endif
