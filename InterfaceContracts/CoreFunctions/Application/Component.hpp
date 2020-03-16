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
    TypeInputInterface< InterfaceA > a_in;
    TypeOutputInterface< InterfaceA > a_out;

    void doPreconditionCheck( );
    void doPostConditionCheck( );
    void initialize( );
    void compute( );
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_HPP_
