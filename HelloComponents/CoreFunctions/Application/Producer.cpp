#include "Producer.hpp"


  void Producer::doPreconditionCheck( )
  {
    // do something clever
    InterfaceA a;
    a = this->a_in.getValue( );
    if ( this->a_in.getValue( ).velocity.getErrorCode( )
         == SafeTypeErrorCode::OVERFLOW ) {
      a.velocity = 0.4F;  // this will cause an underflow.
      this->_error = Producer::ErrorCode::BAD_INPUT_DATA;
    }
    ( void )a;
  }

  void Producer::doPostConditionCheck( )
  {
    // nothing till now.
  }

  void Producer::initialize( )
  {
  }
  void Producer::compute( )
  {
  }
