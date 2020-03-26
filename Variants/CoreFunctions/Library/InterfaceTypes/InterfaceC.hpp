#ifndef INTERFACE_C_HPP_
#define INTERFACE_C_HPP_

#include <BoundedTypes/CustomTypes.hpp>
#include <BoundedTypes/SafeTypes.hpp>
#include <Library/InterfaceTypes/Type_HighAssuranceInterface.hpp>

namespace RomanoViolet
{
  class InterfaceC
  {
  public:
    InterfaceC( ) = default;

    RomanoViolet::SafeType< 0, 14 > accelerationLimits{4};
    RomanoViolet::SafeType< 2, 3, 9, 10 > jerkLimits{0.8F};

  private:
  };  // namespace InterfaceC
}  // namespace RomanoViolet

#endif  // INTERFACE_C_HPP_
