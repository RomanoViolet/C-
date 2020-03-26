#include <Application/Variant_AdditionInterface.hpp>

namespace RomanoViolet
{
  void
  Variant< BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >::doPreconditionCheck( )
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

  void
  Variant< BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >::doPostConditionCheck( )
  {
    // nothing till now.
  }

  void Variant< BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >::initialize( )
  {
  }
  void Variant< BaseComponent::SuportedVariants::WITH_ADDITIONAL_INTERFACES >::compute( )
  {
  }
}  // namespace RomanoViolet
