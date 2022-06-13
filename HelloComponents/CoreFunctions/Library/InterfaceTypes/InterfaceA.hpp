#ifndef INTERFACE_A_HPP_
#define INTERFACE_A_HPP_

#include <InterfaceTypes/CustomTypes.hpp>
#include <InterfaceTypes/SafeTypes.hpp>
#include <InterfaceTypes/Type_HighAssuranceInterface.hpp>

  class InterfaceA
  {
  public:
    InterfaceA( ) = default;

    SafeType< 1, 4 > minWithIntegerBounds{ 2.F };
    VelocityType velocity{ 0.51F };

  private:
  };

#endif  // INTERFACE_A_HPP_
