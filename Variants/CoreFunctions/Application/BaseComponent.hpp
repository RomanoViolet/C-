#ifndef BASECOMPONENT_HPP_
#define BASECOMPONENT_HPP_

#include <Library/ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <Library/InterfaceTypes/InterfaceA.hpp>
#include <Library/InterfaceTypes/InterfaceB.hpp>
#include <Library/InterfaceTypes/Type_InputInterface.hpp>
#include <Library/InterfaceTypes/Type_OutputInterface.hpp>
namespace RomanoViolet
{
  class BaseComponent : public TypeHighAssuranceComponent
  {
  public:
    enum class ErrorCode : short { NO_ERROR = 0U, BAD_INPUT_DATA = 1U };

    BaseComponent( )
        : a_in( TypeInputInterface< InterfaceA >( ) ), b_out( TypeOutputInterface< InterfaceB >( ) )
    {
    }
    TypeInputInterface< InterfaceA > a_in;
    TypeOutputInterface< InterfaceB > b_out;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );

  private:
    ErrorCode _error;
  };
}  // namespace RomanoViolet

#endif  // BASECOMPONENT_HPP_
