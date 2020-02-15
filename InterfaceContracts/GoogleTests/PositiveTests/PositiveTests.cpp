#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <Library/Type_InputInterface.hpp>

TEST( DummyTest, 1 )
{
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

  class MyInterface
  {
  public:
    MyInterface( ) = default;

  private:
    InputInterface< short > i1;
    InputInterface< double > i2;
    void i1.preprocessInputs( ) override
    {
      // something here/
    }

    void i2.preprocessInputs( ) override
    {
      // something here.
    }
  };

  MyInterface interface;
  EXPECT_TRUE( true );
}
