#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <InterfaceTypes/InterfaceA.hpp>
#include <InterfaceTypes/InterfaceB.hpp>
#include <InterfaceTypes/Type_InputInterface.hpp>
#include <InterfaceTypes/Type_OutputInterface.hpp>

  class Producer : public TypeHighAssuranceComponent
  {
  public:
    enum class ErrorCode : short { NO_ERROR = 0U, BAD_INPUT_DATA = 1U };

    Producer( )
        :  b_out( TypeOutputInterface< InterfaceB >( ) )
    {
    }
    TypeOutputInterface< InterfaceB > b_out;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );

  private:
    ErrorCode _error;
  };

#endif  // PRODUCER_HPP_
