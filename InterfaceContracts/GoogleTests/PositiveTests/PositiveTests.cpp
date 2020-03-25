#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Application/Component.hpp>

TEST( DummyTest, 1 )
{
  RomanoViolet::Component c;
  RomanoViolet::InterfaceA a;
  // a.doPreconditionCheck( );
  a.minWithIntegerBounds = 0.37F;
  a.velocity = 0.93F;
  c.a_in.setValue( a );
  c.initialize( );
  c.compute( );
  ( void )c.b_out.getValue( );
  ( void )c;
  EXPECT_TRUE( true );
}
