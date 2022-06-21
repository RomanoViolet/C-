#ifndef TYPE_INPUT_INTERFACE_INL_
#define TYPE_INPUT_INTERFACE_INL_

template < typename T >
const T &TypeInputInterface< T >::getValue( ) const
{
  // dummy return
  return ( this->_value );
}

template < typename T >
void TypeInputInterface< T >::setValue( const T &value )
{
  this->_value = value;
}

#endif  // TYPE_INPUT_INTERFACE_INL_
