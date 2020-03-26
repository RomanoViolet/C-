#include <Application/BaseComponent.hpp>

namespace RomanoViolet
{
  void BaseComponent::doPreconditionCheck( )
  {
    // do something clever
    InterfaceA a;
    a = this->a_in.getValue( );
    if ( this->a_in.getValue( ).velocity.getErrorCode( )
         == RomanoViolet::SafeTypeErrorCode::OVERFLOW ) {
      a.velocity = 0.4F;  // this will cause an underflow.
      this->_error = BaseComponent::ErrorCode::BAD_INPUT_DATA;
    }
    ( void )a;
  }

  void BaseComponent::doPostConditionCheck( )
  {
    // nothing till now.
  }

  void BaseComponent::initialize( )
  {
  }
  void BaseComponent::compute( )
  {
  }
}  // namespace RomanoViolet
