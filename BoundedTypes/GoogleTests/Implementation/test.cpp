#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <Library/CustomTypes.hpp>
#include <Library/SafeTypes.hpp>
#include <limits>

/**
 * @brief Units tests for each requirement associated to Component B.
 *
 */
/*
TEST( InstantationTest, T1 )
{
  RomanoViolet::SafeType< 1, 4 > minWithIntegerBounds;
  EXPECT_TRUE( true );
}

TEST( InstantationTest, T2 )
{
  RomanoViolet::SafeType< 1, 4, 2, 4 > minWithFloatBounds;
  EXPECT_FLOAT_EQ( minWithFloatBounds.getMinValue( ), 0.25F );
}

TEST( InstantationTest, T3 )
{
  RomanoViolet::SafeType< Fraction( 1, 4 ), 2, 4 > minWithFloatBounds;
  EXPECT_TRUE( true );
}

TEST( InstantationTest, T4 )
{
  VelocityType v;
  EXPECT_FLOAT_EQ( v.getMinValue( ), 0.5F );
}
*/

TEST( InstantationTest, OverflowCheck )
{
  // check whether min <= max assertion test will cause an overflow.
  // Tests:
  //      1                 2
  // -------------  <=  ----------------
  // MAX_INT_VALUE     MAX_INT_VALUE
  // Or
  // (2 * MAX_INT_VALUE) <= MAX_INT_VALUE
  //     |
  //     |______(overflow may happen in this expression)
  //
  const int MaxValueOfInt = std::numeric_limits< int >::max( );
  using customType
      = RomanoViolet::SafeType< Fraction( 1, MaxValueOfInt ), Fraction( 2, MaxValueOfInt ) >;
  customType c = 1.0F / MaxValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), 1.0F / MaxValueOfInt );
}

TEST( InstantationTest, OverflowCheck_2 )
{
  // check whether min <= max assertion test will cause an overflow.
  // Tests:
  // (MAX_INT_VALUE-1)        MAX_INT_VALUE
  // ------------------  <=  ----------------
  //    MAX_INT_VALUE                1
  // Or
  // (MAX_INT_VALUE - 1) <= (MAX_INT_VALUE * MAX_INT_VALUE)
  //                                    |
  //                                    |
  //                    (overflow may happen in this expression)
  //
  const int MaxValueOfInt = std::numeric_limits< int >::max( );
  using customType = RomanoViolet::SafeType< Fraction( MaxValueOfInt - 1, MaxValueOfInt ),
                                             Fraction( MaxValueOfInt, 1 ) >;
  customType c = ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt );
}

TEST( InstantationTest, CheckForSignRobustness )
{
  // A negative value for fraction by putting negative sign in the denominator must be evaluated as
  // having negative sign in the numerator. Tests:
  //  (MAX_INT_VALUE-1)        MAX_INT_VALUE
  //  ------------------  <=  ----------------
  //    -MAX_INT_VALUE                1
  // Or
  // (MAX_INT_VALUE - 1) <= (-MAX_INT_VALUE * MAX_INT_VALUE) (INCORRECT. Equality has been
  // reversed.)
  //
  //*********************************************************************
  //                               EXPECTATION
  //*********************************************************************
  //  (MAX_INT_VALUE-1)        MAX_INT_VALUE
  //  ------------------  <=  ----------------
  //    -MAX_INT_VALUE                1
  //
  // transformed to:
  //  -(MAX_INT_VALUE-1)        MAX_INT_VALUE
  //  ------------------  <=  ----------------
  //    MAX_INT_VALUE                1
  //
  // Or
  // -(MAX_INT_VALUE - 1) <= (MAX_INT_VALUE * MAX_INT_VALUE) (INCORRECT.)
  //                                    |
  //                                    |
  //                    (overflow may happen in this expression)
  //
  const int MaxValueOfInt = std::numeric_limits< int >::max( );
  using customType = RomanoViolet::SafeType< Fraction( MaxValueOfInt - 1, MaxValueOfInt ),
                                             Fraction( MaxValueOfInt, 1 ) >;
  customType c = ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt );
}

TEST( InstantationTest, T6 )
{
  CountingType c = 3;
  EXPECT_EQ( c.getValue( ), 3 );
}
