#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Library/HighAssuranceInterface.hpp>
#include <Library/Type_InputInterface.hpp>

TEST( DummyTest, 1 )
{
  float a{1.956F};
  InputInterface< float > A;
  A.setValue( a );

  RomanoViolet::HighAssuranceInterface interface;
  interface.addInputInterface( A );

  /**
   * @brief What is needed
   *
   * class MyInterface
   * {
   *  private:
   *    InputInterface<float> i1;
   *    InputInterface<short> i2;
   *    OutputInterface<float> o1;
   * };
   *
   */

  EXPECT_TRUE( true );
}
