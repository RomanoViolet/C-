#ifndef TYPE_OUTPUT_INTERFACE_INL_
#define TYPE_OUTPUT_INTERFACE_INL_

template < typename T >
TypeOutputInterface< T >::TypeOutputInterface( const T value )
{
  if ( this->_value ) {
    *this->_value = value;
    this->isInitialized = true;
  }
}

template < typename T >
T TypeOutputInterface< T >::getValue( ) const
{
  // dummy return
  return ( *this->_value );
}

template < typename T >
void TypeOutputInterface< T >::doPostConditionCheck( )
{
}

template < typename T >
void TypeOutputInterface< T >::setReference( T &&ref )
{
  this->_value = ref;
}

template < typename T >
TypeOutputInterface< T >::operator T *( )
{
  return this->_value;
}
#endif  // TYPE_OUTPUT_INTERFACE_INL_
