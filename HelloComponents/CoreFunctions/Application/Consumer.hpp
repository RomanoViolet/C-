#ifndef CONSUMER_HPP_
#define CONSUMER_HPP_

#include <ComponentTypes/Type_HighAssuranceComponent.hpp>
#include <InterfaceTypes/Type_InputInterface.hpp>
#include <InterfaceTypes/Type_OutputInterface.hpp>

#include <cstdint>
class Consumer : public TypeHighAssuranceComponent
{
public:
  enum class ErrorCode : short { NO_ERROR = 0U, BAD_INPUT_DATA = 1U };

  Consumer( ) : a_in( TypeInputInterface< int16_t >( ) )
  {
  }
  TypeInputInterface< int16_t > a_in;

  void initialize( );
  void doPreconditionCheck( );
  void compute( );
  void doPostConditionCheck( );

#ifndef NDEBUG
  // debug mode
  int16_t getStoredValue( );
#endif

private:
  ErrorCode _error;
};

#endif
