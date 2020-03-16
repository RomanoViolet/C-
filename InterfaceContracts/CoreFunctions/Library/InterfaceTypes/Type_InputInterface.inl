#ifndef TYPE_INPUT_INTERFACE_INL_
#define TYPE_INPUT_INTERFACE_INL_

namespace RomanoViolet
{
  template < typename T >
  T &TypeInputInterface< T >::getValue( ) const
  {
    // dummy return
    return ( T( ) );
  }

  template < typename T >
  void TypeInputInterface< T >::setValue( const T &value )
  {
    this->_value = value;
  }

  template < typename T >
  void TypeInputInterface< T >::doPreconditionCheck( )
  {
    this->_value.doPreconditionCheck( );
  }
}  // namespace RomanoViolet
#endif  // TYPE_INPUT_INTERFACE_INL_
