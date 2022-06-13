#ifndef INTERFACE_B_HPP_
#define INTERFACE_B_HPP_

#include <InterfaceTypes/CustomTypes.hpp>
#include <InterfaceTypes/SafeTypes.hpp>
#include <InterfaceTypes/Type_HighAssuranceInterface.hpp>

  class InterfaceB
  {
  public:
    InterfaceB( ) = default;

    SafeType< 1, 4 > minWithIntegerBounds{2.F};
    VelocityType velocity{0.51F};

  private:
  };  // namespace InterfaceB

#endif  // INTERFACE_B_HPP_
