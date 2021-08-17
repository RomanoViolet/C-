#ifndef INTERFACE_D_HPP_
#define INTERFACE_D_HPP_

#include <BoundedTypes/CustomTypes.hpp>
#include <BoundedTypes/SafeTypes.hpp>

namespace RomanoViolet
{
  class InterfaceD
  {
  public:
    InterfaceD( ) = default;

    RomanoViolet::SafeType< 1, 10, 3, 10 > throttle{0.1F};

  private:
  };  // namespace InterfaceD
}  // namespace RomanoViolet

#endif  // INTERFACE_D_HPP_
