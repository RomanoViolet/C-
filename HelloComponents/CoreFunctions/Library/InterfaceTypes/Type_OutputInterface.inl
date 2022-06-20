#ifndef TYPE_OUTPUT_INTERFACE_INL_
#define TYPE_OUTPUT_INTERFACE_INL_

template < typename T >
T TypeOutputInterface< T >::getValue( ) const
{
  // dummy return
  return ( this->_value );
}

template < typename T >
void TypeOutputInterface< T >::doPostConditionCheck( )
{
  this->_value.doPreconditionCheck( );
}
#endif  // TYPE_OUTPUT_INTERFACE_INL_
