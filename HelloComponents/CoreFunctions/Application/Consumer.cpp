#include "Consumer.hpp"

void Consumer::initialize( )
{
}

void Consumer::compute( )
{
}

void Consumer::doPreconditionCheck( )
{
  // do something clever
  InterfaceA a;
  a = this->a_in.getValue( );
  if ( this->a_in.getValue( ).velocity.getErrorCode( ) == SafeTypeErrorCode::OVERFLOW ) {
    a.velocity = 0.4F;  // this will cause an underflow.
    this->_error = Consumer::ErrorCode::BAD_INPUT_DATA;
  }
  ( void )a;
}

void Consumer::doPostConditionCheck( )
{
  // nothing till now.
}
