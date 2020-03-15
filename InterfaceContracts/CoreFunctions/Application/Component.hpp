#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <Library/ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <Library/InterfaceTypes/InterfaceA.hpp>
#include <Library/InterfaceTypes/Type_InputInterface.hpp>
#include <Library/InterfaceTypes/Type_OutputInterface.hpp>
namespace RomanoViolet
{
  class Component : public TypeHighAssuranceComponent
  {
  public:
    Component( ) = default;
    TypeInputInterface< InterfaceA > a;
    TypeOutputInterface< InterfaceA > a_out;

    void doPreconditionCheck( );
    void doPostConditionCheck( );
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_HPP_
