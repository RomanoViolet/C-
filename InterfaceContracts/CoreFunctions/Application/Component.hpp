#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <Library/ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <Library/InterfaceTypes/InterfaceA.hpp>
#include <Library/InterfaceTypes/InterfaceB.hpp>
#include <Library/InterfaceTypes/Type_InputInterface.hpp>
#include <Library/InterfaceTypes/Type_OutputInterface.hpp>
namespace RomanoViolet
{
  class Component : public TypeHighAssuranceComponent
  {
  public:
    Component( )
        : a_in( TypeInputInterface< InterfaceA >( ) ), b_out( TypeOutputInterface< InterfaceB >( ) )
    {
    }
    TypeInputInterface< InterfaceA > a_in;
    TypeOutputInterface< InterfaceB > b_out;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );
  };
}  // namespace RomanoViolet

#endif  // COMPONENT_HPP_
