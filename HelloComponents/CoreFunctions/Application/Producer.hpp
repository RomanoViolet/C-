#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_
#include <cstdint>
#include <ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <InterfaceTypes/Type_InputInterface.hpp>
#include <InterfaceTypes/Type_OutputInterface.hpp>

  class Producer : public TypeHighAssuranceComponent
  {
  public:
    enum class ErrorCode : short { NO_ERROR = 0U, BAD_INPUT_DATA = 1U };

    Producer( )
        :  a_out(  TypeOutputInterface< int16_t >{45U})
    {
    }
    TypeOutputInterface< int16_t > a_out;

    void initialize( );
    void doPreconditionCheck( );
    void compute( );
    void doPostConditionCheck( );

  private:
    ErrorCode _error;
  };

#endif  // PRODUCER_HPP_
