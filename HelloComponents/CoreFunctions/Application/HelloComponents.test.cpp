#include "ComponentTypes/SharedMemoryConnect.hpp"
#include "Consumer.hpp"
#include "Producer.hpp"
#include <cstdint>
#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#ifndef NDEBUG
TEST( BaseTests, Instantiation )  // NOLINT
{
  Producer p;
  Consumer c;
  SharedMemoryConnect< int16_t > shm;
  shm.from( p.a_out.toPtr( ) ).to( c.a_in.toPtr( ) );
  p.compute( );
  EXPECT_EQ( c.getStoredValue( ), 37U );
}
#endif

/**
 * @brief Verifies that a segmentation fault occurs if the network
 *        is not attached between producer and consumer.
 *
 */
TEST( BaseTests, SegfaultOnNoNetwork )  // NOLINT
{
  Producer p;
  Consumer c;
  // EXPECT_DEATH( p.compute( ), "Segmentation fault*" );
  // EXPECT_DEATH( c.getStoredValue( ), "Segmentation fault*" );
  ASSERT_EXIT( ( p.compute( ), exit( 0 ) ), ::testing::KilledBySignal( SIGSEGV ), ".*" );
  ASSERT_EXIT( ( c.getStoredValue( ), exit( 0 ) ), ::testing::KilledBySignal( SIGSEGV ), ".*" );
}
