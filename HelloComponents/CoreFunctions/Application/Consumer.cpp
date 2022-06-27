#include "Consumer.hpp"
#include <iostream>
void Consumer::initialize( )
{
}

void Consumer::compute( )
{
  // read the value from producer and add 1 to it.
  std::cout << "Received: " << this->a_in.getValue( ) << ". Is now: " << this->a_in.getValue( ) + 1
            << std::endl;
}

void Consumer::doPreconditionCheck( )
{
  // do something clever
  int16_t a;
  a = this->a_in.getValue( );
  ( void )a;

  this->_error = ErrorCode::NO_ERROR;
}

void Consumer::doPostConditionCheck( )
{
  // nothing till now.
}

#ifndef NDEBUG
// debug mode
int16_t Consumer::getStoredValue( )
{
  return this->a_in.getValue( );
}
#endif
