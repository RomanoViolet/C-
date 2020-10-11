#include "CastFromEnum.hpp"
#include "TypeAsOperator.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest.h"
#include <ctime>
#include <string>
#include <type_traits>
TEST( Operators, FloatTypeAcceptance )
{
  TypeAsOperator< float > typeAsOperator{ 4.5F };
  // assign the value of the object, a float. Conversion is handled inside the class itself
  float float_response = typeAsOperator;
  EXPECT_FLOAT_EQ( 4.5F, float_response );

  // assign the value of the object, a float to an int. Type conversion handled by the class.
  int int_response = typeAsOperator;
  EXPECT_EQ( int_response, 4 );

  // assign the value of the object, a float to an double. Type conversion handled by the class.
  double double_response = typeAsOperator;
  EXPECT_DOUBLE_EQ( 4.5, double_response );

  // assign the value of the object, a float to an bool. Type conversion handled by the class.
  bool bool_response = typeAsOperator;
  EXPECT_TRUE( bool_response );
}

TEST( Operators, DoubleTypeAcceptance )
{
  TypeAsOperator< double > myOperators{ 4.5 };

  double double_response = myOperators;
  EXPECT_DOUBLE_EQ( 4.5, double_response );

  // assign the value of the object, a double to an float. Type conversion handled by the class.
  float float_response = myOperators;
  EXPECT_FLOAT_EQ( 4.5F, float_response );

  // assign the value of the object, a double to an int. Type conversion handled by the class.
  int int_response = myOperators;
  EXPECT_EQ( 4, int_response );

  // assign the value of the object, a double to a bool. Type conversion handled by the class.
  bool bool_response = myOperators;
  EXPECT_TRUE( bool_response );
}

TEST( Operators, CastFromEnumTest )
{
  CastFromEnum e;
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  int int_response = e;
  EXPECT_EQ( int_response, static_cast< int >( CastFromEnum::MyEnumeration::OK ) );

  CastFromEnum e2{ CastFromEnum::MyEnumeration::APOCALYPSE };
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  float float_response = e2;
  EXPECT_FLOAT_EQ( float_response,
                   static_cast< float >( CastFromEnum::MyEnumeration::APOCALYPSE ) );

  CastFromEnum e3{ CastFromEnum::MyEnumeration::ERROR };
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  double double_response = e3;
  EXPECT_DOUBLE_EQ( double_response, static_cast< double >( CastFromEnum::MyEnumeration::ERROR ) );

  CastFromEnum e4{ CastFromEnum::MyEnumeration::ERROR };
  // assign the value of the object, an enumeration. Conversion is handled inside the class itself
  bool bool_response = e3;
  EXPECT_FALSE( bool_response );
}
