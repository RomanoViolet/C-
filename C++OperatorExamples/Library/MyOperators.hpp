#ifndef MY_OPERATORS_INCLUDED
#define MY_OPERATORS_INCLUDED
#include <string>
#include <type_traits>

/// @see https://en.cppreference.com/w/cpp/types/enable_if
template < typename T, class Enable = void >
class MyOperators
{
};

template < typename T >
class MyOperators<
    T,
    typename std::enable_if< std::is_floating_point< T >::value || std::is_integral< T >::value
                             || std::is_arithmetic< T >::value
                             // || std::is_same< T, std::string >::value
                             >::type >
    final
{
public:
  MyOperators( const T value ) : _value( value )
  {
  }
  operator float( )
  {
    return static_cast< float >( this->_value );
  }

  operator double( )
  {
    return static_cast< double >( this->_value );
  }

  operator int( )
  {
    return static_cast< int >( this->_value );
  }

  operator bool( )
  {
    if ( this->_value > 0 ) {
      return true;
    } else {
      return false;
    }
  }

private:
  T _value;
};

#endif
