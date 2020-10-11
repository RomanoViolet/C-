#include "MyOperators.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"
#include <string>
#include <type_traits>
TEST( Operators, FloatTypeAcceptance )
{
  MyOperators< float > myOperators{ 4.5F };
  float float_response = myOperators;
  EXPECT_FLOAT_EQ( 4.5F, float_response );

  int int_response = myOperators;
  EXPECT_EQ( int_response, 4 );

  double double_response = myOperators;
  EXPECT_DOUBLE_EQ( 4.5, double_response );

  bool bool_response = myOperators;
  EXPECT_TRUE( bool_response );
}

TEST( Operators, DoubleTypeAcceptance )
{
  MyOperators< double > myOperators{ 4.5 };
  double double_response = myOperators;
  EXPECT_DOUBLE_EQ( 4.5, double_response );

  float float_response = myOperators;
  EXPECT_FLOAT_EQ( 4.5F, float_response );

  int int_response = myOperators;
  EXPECT_EQ( 4, int_response );

  bool bool_response = myOperators;
  EXPECT_TRUE( bool_response );
}

TEST( Operators, StringTypeAcceptance )
{
  auto testFrame = []( ) {
    MyOperators< std::string > myOperators{ "hello" };
    ( void )myOperators;
  };

  // https://godbolt.org/z/9bP9bd
  // https://godbolt.org/z/cEYx65 (With std::string not part of MyOperators signature)
  // https://godbolt.org/z/jas87z
  ASSERT_DEATH( testFrame( ), "error:" );
}
