#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <CustomTypes.hpp>
#include <SafeTypes.hpp>
#include <limits>
#include <type_traits>

TEST( InstantationTest, CheckForZeroDenominator )
{
#if ( defined( __GNUC__ ) || defined( __clang__ ) )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

  // long version
  // auto f
  //     = []( ) { return ( std::is_constructible< RomanoViolet::SafeType< 1, 0, 1, 1 > >::value );
  //     };

  // EXPECT_FALSE( f( ) );

  // lambda was necessary to get around limitations of macros with carats.
  EXPECT_FALSE( []( ) {
    return ( std::is_constructible< RomanoViolet::SafeType< 1, 0, 1, 1 > >::value );
  }( ) );

  // const int MaxValueOfInt = 1;
  // using customType = RomanoViolet::SafeType< Fraction( 1, 0 ), Fraction( MaxValueOfInt, 1 ) >;
  // customType c = 0.9;  // actual value does not matter.
#if ( defined( __clang__ ) || defined( __GNUC__ ) )
#pragma GCC diagnostic pop
#endif
}

TEST( InstantationTest, VerifyThatTwoUnrelatedTypesCannotBeAdded )
{
  // GTEST_SKIP( );

  const int MinValueOfInt = 3;
  const int MaxValueOfInt = 5;

  using customType
      = RomanoViolet::SafeType< Fraction( MinValueOfInt, 2 ), Fraction( MaxValueOfInt, 2 ) >;

  using differentCustomType = RomanoViolet::SafeType< Fraction( 2 * MinValueOfInt, 2 ),
                                                      Fraction( 2 * MaxValueOfInt, 2 ) >;

  // customType e = c + d;
  //            -------
  //               |____ this should fail.
  //
  // TODO: Is this the correct approach?
  EXPECT_FALSE( []( ) {
    return ( std::is_constructible< customType, customType, differentCustomType >::value );
  }( ) );
}
