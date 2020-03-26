#ifndef COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
#define COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
#include <Application/Component.hpp>
#include <Library/InterfaceTypes/InterfaceC.hpp>

namespace RomanoViolet
{
  class ComponentVariantWithAdditionalInterfaces : public BaseComponent
  {
  public:
    ComponentVariantWithAdditionalInterfaces( ) = default;
    TypeInputInterface< InterfaceC > c_in;
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
