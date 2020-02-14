#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Library/HighAssuranceInterface.hpp>
#include <Library/Type_InputInterface.hpp>
TEST( DummyTest, 1 )
{
  float a{1.956F};
  InputInterface< float > A;
  A.setValue( a );

  EXPECT_TRUE( true );
}
