#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <CustomTypes.hpp>
#include <SafeTypes.hpp>
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
  customType c{ 1.0F / MaxValueOfInt };
  EXPECT_FLOAT_EQ( c, 1.0F / MaxValueOfInt );
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
  customType c{ ( float( MaxValueOfInt ) - 1.0F ) / MaxValueOfInt };
  EXPECT_FLOAT_EQ( c, ( float( MaxValueOfInt ) - 1.0F ) / MaxValueOfInt );
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
  customType c{ ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / MaxValueOfInt };
  EXPECT_FLOAT_EQ( c, ( MaxValueOfInt * 1.0F - MaxValueOfInt ) / -MaxValueOfInt );
}

TEST( InstantationTest, CheckForAllNegativeBounds_1 )
{
  // Test when bound lower and upper bounds are negative.
  // https://gcc.godbolt.org/z/NEm_DK

  const int MinValueOfInt = std::numeric_limits< int >::min( ) + 1;
  using customType
      = RomanoViolet::SafeType< Fraction( 2, MinValueOfInt ), Fraction( 1, MinValueOfInt ) >;
  customType c{ 1.5F / MinValueOfInt };
  EXPECT_FLOAT_EQ( c, 1.5F / MinValueOfInt );
}

TEST( InstantationTest, CheckForAllNegativeBounds_2 )
{
  // Test when lower and upper bounds are negative.
  // https://gcc.godbolt.org/z/NEm_DK

  const int MaxValueOfInt = std::numeric_limits< int >::max( );
  using customType
      = RomanoViolet::SafeType< Fraction( -2, MaxValueOfInt ), Fraction( -1, MaxValueOfInt ) >;
  customType c{ -1.5F / MaxValueOfInt };
  EXPECT_FLOAT_EQ( c, -1.5F / MaxValueOfInt );
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
  customType c{ value };
  EXPECT_FLOAT_EQ( c, value );
}

TEST( InstantationTest, CheckForResolution )
{
  // Test when lower and upper bounds are very close to each other

  const int MinValueOfInt = std::numeric_limits< int >::min( ) + 1;
  const int MaxValueOfInt = std::numeric_limits< int >::max( );

  const int range_from = -100;
  const int range_to = 100;
  std::random_device rand_dev;
  std::mt19937 generator( rand_dev( ) );

  std::uniform_int_distribution< int > distr( range_from, range_to );

  float value
      = ( float( distr( generator ) ) / distr( generator ) )
        * ( ( ( 1.0F / MaxValueOfInt ) - ( 1.0F / MinValueOfInt ) ) / ( range_from - range_to ) );
  using customType
      = RomanoViolet::SafeType< Fraction( 1, MinValueOfInt ), Fraction( 1, MaxValueOfInt ) >;
  customType c{ value };
  EXPECT_FLOAT_EQ( c, value );
}

TEST( InstantationTest, CheckForFlooring )
{
  // Test when lower and upper bounds are very close to each other

  const int MinValueOfInt = -3;
  const int MaxValueOfInt = 5;

  float value = -3.1F;

  // note: A denominator of 1 will automatically match against integer
  // specialization of safetype.
  //       That is, a float value cannot be stored inside.
  //       Setting the denominator to 1.0F will not work since all numerators and
  //       denominators are exepected to be of type int
  using customType
      = RomanoViolet::SafeType< Fraction( 1, MinValueOfInt ), Fraction( 1, MaxValueOfInt ) >;
  customType c{ value };

  // Stored value will be floored to the lower bound.
  EXPECT_FLOAT_EQ( c, -1.0F / 3.F );
}

TEST( InstantationTest, CheckForCeiling_FloatSpecialization )
{
  // Test when value to be assigned is higher than upper bound, and is therefore expected to be
  // ceiled to the upper bound.

  const int MinValueOfInt = 3;
  const int MaxValueOfInt = 5;

  float value = 10.F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;
  customType c{ value };

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( c, 5.0 / 2.0F );
}

TEST( InstantationTest, CheckForCeiling_IntegerSpecialization )
{
  // Test when value to be assigned is higher than upper bound, and is therefore expected to be
  // ceiled to the upper bound.

  const int MinValueOfInt = 3;
  const int MaxValueOfInt = 5;

  float value = 10.F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
  customType c{ value };

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( c, 5.0F );
}

// The following test is disabled because operator float() is removed.
// This operator allowed addition (and other operations) on unrelated types
// since it will first extract the float value embedded in the object and pass it to the
// operator such as +, which accepts a float.
//
// TEST( InstantationTest, AssignmentToFloat )
// {

//   // Tests whether the value stored in the class can be assigned to a float (the type value is
//   // stored in the class)
//   //
//   // customType c = <some value>
//   // float x = c;
//   //         |_________ Test this.
//   //

//   const int MinValueOfInt = -2;
//   const int MaxValueOfInt = 1;

//   float value = -0.73F;
//   using customType
//       = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
//   customType c = value;
//   float cNew = c;  // this assignment is being tested.

//   // Stored value will be ceiled to the upper bound
//   EXPECT_FLOAT_EQ( c, cNew );
// }

TEST( InstantationTest, CopyConstructor )
{
  // Test the copy constructor

  const int MinValueOfInt = -2;
  const int MaxValueOfInt = 1;

  float value = -0.73F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
  customType c{ value };

  customType newObject = c;

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( c, newObject );
}

TEST( InstantationTest, AssignmentOperator )
{
  // Test the copy constructor

  const int MinValueOfInt = -2;
  const int MaxValueOfInt = 1;

  float value = -0.73F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
  customType c{ value };

  customType c_other{ 0.995 };  // as long as it is within the bounds of the customType

  c_other = c;  // This is being tested.

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( c, c_other );
}

TEST( InstantationTest, AdditionWithAnotherFloat )
{
  // Binary arithmetic with other floats should work out of the box due to operator float() being
  // implemented.

  const int MinValueOfInt = -2;
  const int MaxValueOfInt = 1;

  float value = -0.73F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 1 ), Fraction( MaxValueOfInt, 1 ) >;
  customType c{ value };

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( c + 1.3F, value + 1.3F );
}

TEST( InstantationTest, AdditionOperator )
{
  // Test addition.

  const int MinValueOfInt = 3;
  const int MaxValueOfInt = 8;

  float value = 1.5F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;
  customType c{ value };

  customType d = c;
  customType e = d + c;

  EXPECT_FLOAT_EQ( e, 3.0 );
}

TEST( InstantationTest, AdditionOperatorWithCeiling )
{
  // Test when value to be assigned after addition exceeds the upper bound.
  // Expect that the value is ceiled to the upper bound.

  const int MinValueOfInt = 3;
  const int MaxValueOfInt = 5;

  float value = 10.F;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;
  customType c{ value };

  customType d = c;
  customType e = d + c;

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( e, 2.5 );
}

TEST( InstantationTest, SubtractionOperator )
{
  const int MinValueOfInt = 1;
  const int MaxValueOfInt = 5;

  float value = 2.5;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;
  customType d{ value };  // 2.5

  customType e{ 1.5F };
  customType f = d - e;  // 1.0

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( f, 1.0F );
}

TEST( InstantationTest, SubtractionOperatorWithFlooring )
{
  // the result of subtraction falls below the lower bound, and needs to be floored.
  const int MinValueOfInt = 1;
  const int MaxValueOfInt = 5;

  float value = 2.5;
  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;
  customType d{ value };  // 2.5

  customType e{ 4.5F };
  // e = 4.5F;
  customType f = d - e;  // 1.0

  // Stored value will be ceiled to the upper bound
  EXPECT_FLOAT_EQ( f, 0.5F );
}

TEST( InstantationTest, Demo )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.5F };

  VelocityType w{ v + 0.20F };
  EXPECT_FLOAT_EQ( w, 0.70F );
}

TEST( ErrorCodes, Underflow )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.4F };
  EXPECT_FLOAT_EQ( v, 0.5F );
  EXPECT_EQ( v.getErrorCode( ), RomanoViolet::SafeTypeErrorCode::UNDERFLOW );
}

TEST( ErrorCodes, Overflow )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.8F };
  EXPECT_FLOAT_EQ( v, 0.75F );
  EXPECT_EQ( v.getErrorCode( ), RomanoViolet::SafeTypeErrorCode::OVERFLOW );
}

TEST( InstantationTest, OverflowCausedByOperation )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.5F };

  VelocityType w{ v + 0.30F };
  EXPECT_FLOAT_EQ( w, 0.75F );
  EXPECT_EQ( w.getErrorCode( ), RomanoViolet::SafeTypeErrorCode::OVERFLOW );
}

TEST( InstantationTest, UnderflowCausedByOperation )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.5F };

  VelocityType w{ v - 0.30F };
  EXPECT_FLOAT_EQ( w, 0.50F );
  EXPECT_EQ( w.getErrorCode( ), RomanoViolet::SafeTypeErrorCode::UNDERFLOW );
}

TEST( InstantationTest, UnderflowCausedByOperationUsingFloatOperator )
{
  // Lower bound: 1/2 = 0.5F. Upper bound: 3/4 = 0.75F
  VelocityType v{ 0.5F };

  VelocityType w{ v - 0.30F };
  EXPECT_FLOAT_EQ( w, 0.50F );

  float _v = w;
  EXPECT_FLOAT_EQ( _v, 0.50F );

  EXPECT_EQ( w.getErrorCode( ), RomanoViolet::SafeTypeErrorCode::UNDERFLOW );
}
