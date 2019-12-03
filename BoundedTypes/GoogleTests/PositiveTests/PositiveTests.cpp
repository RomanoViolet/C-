#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <Library/CustomTypes.hpp>
#include <Library/SafeTypes.hpp>
#include <limits>
#include <random>

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

TEST( InstantationTest, CheckForAllNegativeBounds_1 )
{
  // Test when bound lower and upper bounds are negative.
  // https://gcc.godbolt.org/z/NEm_DK

  const int MinValueOfInt = std::numeric_limits< int >::min( ) + 1;
  using customType
      = RomanoViolet::SafeType< Fraction( 2, MinValueOfInt ), Fraction( 1, MinValueOfInt ) >;
  customType c = 1.5F / MinValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), 1.5F / MinValueOfInt );
}

TEST( InstantationTest, CheckForAllNegativeBounds_2 )
{
  // Test when bound lower and upper bounds are negative.
  // https://gcc.godbolt.org/z/NEm_DK

  const int MaxValueOfInt = std::numeric_limits< int >::max( );
  using customType
      = RomanoViolet::SafeType< Fraction( -2, MaxValueOfInt ), Fraction( -1, MaxValueOfInt ) >;
  customType c = -1.5F / MaxValueOfInt;
  EXPECT_FLOAT_EQ( c.getValue( ), -1.5F / MaxValueOfInt );
}

TEST( InstantationTest, CheckForNegativeAndPositiveBounds )
{
  // Test when bound lower and upper bounds are negative.
  // https://gcc.godbolt.org/z/NEm_DK

  const int MinValueOfInt = std::numeric_limits< int >::min( ) + 1;
  const int MaxValueOfInt = std::numeric_limits< int >::max( );

  const int range_from = MinValueOfInt;
  const int range_to = MaxValueOfInt;
  std::random_device rand_dev;
  std::mt19937 generator( rand_dev( ) );

  std::uniform_int_distribution< int > distr( range_from, range_to );

  float value = float( distr( generator ) ) / distr( generator );

  // note: A denominator of 1 will automatically match against integer specialization of safetype.
  //       That is, a float value cannot be stored inside.
  //       Setting the denominator to 1.0F will not work since all numerators and denominators are
  //       exepected to be of type int
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
  customType c = value;
  EXPECT_FLOAT_EQ( c.getValue( ), value );
}

TEST( InstantationTest, CheckForResolution )
{
  // Test when lower and upper bounds are very close to each other

  const int MinValueOfInt = std::numeric_limits< int >::min( ) + 1;
  const int MaxValueOfInt = std::numeric_limits< int >::max( );

  const int range_from = MinValueOfInt;
  const int range_to = MaxValueOfInt;
  std::random_device rand_dev;
  std::mt19937 generator( rand_dev( ) );

  std::uniform_int_distribution< int > distr( range_from, range_to );

  float value = float( distr( generator ) ) / distr( generator );
  std::cout << "Value: " << value << ". Random Value stored: " << ( 1.0F / value ) << std::endl;
  std::cout << "Min Bound: " << 1.0 / -2147483647 << ". Max Bound:" << 1.0 / 2147483647
            << std::endl;

  // note: A denominator of 1 will automatically match against integer
  // specialization of safetype.
  //       That is, a float value cannot be stored inside.
  //       Setting the denominator to 1.0F will not work since all numerators and
  //       denominators are exepected to be of type int
  using customType
      = RomanoViolet::SafeType< Fraction( 1, MinValueOfInt ), Fraction( 1, MaxValueOfInt ) >;
  customType c = 1.0F / value;
  EXPECT_FLOAT_EQ( c.getValue( ), 1.0F / value );
}
