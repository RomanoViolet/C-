#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Application/BaseComponent.hpp>
#include <Application/VariantBase.hpp>
#include <Application/Variant_AdditionInterface.hpp>

TEST( DummyTest, 1 )
{
  RomanoViolet::Variant< RomanoViolet::BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >
      c;
  RomanoViolet::InterfaceA a;
  // a.doPreconditionCheck( );
  a.minWithIntegerBounds = 0.37F;
  a.velocity = 0.93F;
  c.a_in.setValue( a );
  c.initialize( );
  c.compute( );
  ( void )c.b_out.getValue( );
  c.doPreconditionCheck( );
  ( void )c;
  EXPECT_TRUE( true );
}
