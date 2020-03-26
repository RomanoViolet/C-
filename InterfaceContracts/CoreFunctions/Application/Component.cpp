#include "Component.hpp"

namespace RomanoViolet
{
  void Component::doPreconditionCheck( )
  {
    // do something clever
    InterfaceA a;
    a = this->a_in.getValue( );
    if ( this->a_in.getValue( ).velocity.getErrorCode( )
         == RomanoViolet::SafeTypeErrorCode::OVERFLOW ) {
      a.velocity = 0.4F;  // this will cause an underflow.
      this->_error = Component::ErrorCode::BAD_INPUT_DATA;
    }
    ( void )a;
  }

  void Component::doPostConditionCheck( )
  {
    // nothing till now.
  }

  void Component::initialize( )
  {
  }
  void Component::compute( )
  {
  }
}  // namespace RomanoViolet
