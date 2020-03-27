#ifndef COMPONENT_VARIANT_IDENTICAL_INTERFACE_HPP_
#define COMPONENT_VARIANT_IDENTICAL_INTERFACE_HPP_
#include <Application/BaseComponent.hpp>
#include <Application/VariantBase.hpp>
#include <Library/InterfaceTypes/InterfaceC.hpp>
#include <Library/InterfaceTypes/InterfaceD.hpp>
namespace RomanoViolet
{
  template <>
  class Variant< BaseComponent::SuportedVariants::WITH_IDENTICAL_INTERFACES > : public BaseComponent
  {
  public:
    Variant( ) : BaseComponent( )
    {
    }

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_VARIANT_IDENTICAL_INTERFACE_HPP_
