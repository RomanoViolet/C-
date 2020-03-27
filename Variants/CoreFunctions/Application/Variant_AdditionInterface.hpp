#ifndef COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
#define COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
#include <Application/BaseComponent.hpp>
#include <Application/VariantBase.hpp>
#include <Application/Variant_AdditionInterface.hpp>
#include <Library/InterfaceTypes/InterfaceC.hpp>
#include <Library/InterfaceTypes/InterfaceD.hpp>
namespace RomanoViolet
{
  template <>
  class Variant< BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >
      : public BaseComponent
  {
  public:
    Variant( ) : BaseComponent( ), c_in( TypeInputInterface< InterfaceC >( ) )
    {
    }

    TypeInputInterface< InterfaceC > c_in;
    TypeOutputInterface< InterfaceD > d_out;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_VARIANT_ADDITIONAL_INTERFACE_HPP_
