#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Application/Component.hpp>

TEST( DummyTest, 1 )
{
  RomanoViolet::Component c;
  RomanoViolet::InterfaceA a;
  // a.doPreconditionCheck( );
  a.minWithIntegerBounds = 0.37F;
  a.velocity = 0.63F;
  c.a_in.setValue( a );
  ( void )c;
  EXPECT_TRUE( true );
}
