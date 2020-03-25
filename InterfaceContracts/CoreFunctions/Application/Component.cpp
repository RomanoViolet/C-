#include "Component.hpp"

namespace RomanoViolet
{
  void Component::doPreconditionCheck( )
  {
    // do something clever
    InterfaceA a;
    if ( this->a_in.getErrorCode( ) )
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
