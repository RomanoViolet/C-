#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Application/Componet.hpp>

TEST( DummyTest, 1 )
{
  RomanoViolet::Component c;
  RomanoViolet::InterfaceA a;
  a.minWithIntegerBounds = 0.37F;
  a.velocity = 0.63F;

  c.a.setValue( a );
  EXPECT_TRUE( true );
}
