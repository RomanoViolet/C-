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
      a.velocity = 0.4F;
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
