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
  using customType = RomanoViolet::SafeType< Fraction( MaxValueOfInt - 1, -MaxValueOfInt ),
                                             Fraction( MaxValueOfInt, 1 ) >;
  customType c = ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / -MaxValueOfInt );
}

TEST( InstantationTest, CheckForZeroDenominator )
{
  //#define EXPECT_DEATH( statement, regex )  EXPECT_EXIT( statement,
  //::testing::internal::ExitedUnsuccessfully, regex )
#if ( defined( __GNUC__ ) || defined( __clang__ ) )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

  // auto f = []( ) {
  //   const int MaxValueOfInt = 1;
  //   using customType = RomanoViolet::SafeType< Fraction( 1, 0 ), Fraction( MaxValueOfInt, 1 )
  //   >; customType c = 0.9;  // actual value does not matter.
  // };
  // EXPECT_DEATH( f( ), "Denominator for lower bound cannot be zero." );

  // Google Test does not seem to provide a convenient method to expect death of a constructor,
  // which is what SafeType does for malformed template arguments.

  // How to test for build or compile time failures.
  // https://stackoverflow.com/questions/30155619/expected-build-failure-tests-in-cmake

  const int MaxValueOfInt = 1;
  typedef RomanoViolet::SafeType< Fraction( 1, 0 ), Fraction( MaxValueOfInt, 1 ) > customType;
  EXPECT_DEATH( customType c = 0.9  // actual value does not matter.
                ,
                "Denominator for lower bound cannot be zero." );

  // const int MaxValueOfInt = 1;
  // using customType = RomanoViolet::SafeType< Fraction( 1, 0 ), Fraction( MaxValueOfInt, 1 ) >;
  // customType c = 0.9;  // actual value does not matter.
#if ( defined( __clang__ ) || defined( __GNUC__ ) )
#pragma GCC diagnostic pop
#endif
}
