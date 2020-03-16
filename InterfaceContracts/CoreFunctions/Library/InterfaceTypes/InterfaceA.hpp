#ifndef INTERFACE_A_HPP_
#define INTERFACE_A_HPP_

#include <Library/BoundedTypes/CustomTypes.hpp>
#include <Library/BoundedTypes/SafeTypes.hpp>
#include <Library/InterfaceTypes/Type_HighAssuranceInterface.hpp>

namespace RomanoViolet
{
  class InterfaceA
  {
  public:
    InterfaceA( ) = default;

    RomanoViolet::SafeType< 1, 4 > minWithIntegerBounds{2.F};
    VelocityType velocity{0.51F};

  private:
  };
}  // namespace RomanoViolet

#endif  // INTERFACE_A_HPP_
