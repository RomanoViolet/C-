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
    enum class SuportedVariants : short {
      WITH_ADDITIONAL_INTERFACES = 0U,
      WITH_IDENTICAL_INTERFACES = 1U
    };
    BaseComponent( )
        : a_in( TypeInputInterface< InterfaceA >( ) )
        , b_out( TypeOutputInterface< InterfaceB >( ) )
        , _error( ErrorCode::NO_ERROR )
    {
    }
    TypeInputInterface< InterfaceA > a_in;
    TypeOutputInterface< InterfaceB > b_out;

    // void initialize( );
    // void doPreconditionCheck( );
    // void compute( );
    // void doPostConditionCheck( );

  protected:
    ErrorCode _error;
  };
}  // namespace RomanoViolet

#endif  // BASECOMPONENT_HPP_
