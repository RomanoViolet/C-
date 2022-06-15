#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <InterfaceTypes/InterfaceA.hpp>
#include <InterfaceTypes/InterfaceB.hpp>
#include <InterfaceTypes/Type_InputInterface.hpp>
#include <InterfaceTypes/Type_OutputInterface.hpp>

  class Consumer : public TypeHighAssuranceComponent
  {
    public:
    enum class ErrorCode : short { NO_ERROR = 0U, BAD_INPUT_DATA = 1U };

    Consumer( )
        : a_in( TypeInputInterface< InterfaceA >( ) )
    {
    }
    TypeInputInterface< InterfaceA > a_in;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );

  private:
    ErrorCode _error;

  };


#endif
