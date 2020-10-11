#ifndef CAST_FROM_ENUM_INCLUDED
#define CAST_FROM_ENUM_INCLUDED
#include <assert.h>
#include <string>
#include <type_traits>

class CastFromEnum final
{
public:
  enum class MyEnumeration : uint8_t { OK = 0U, ERROR = 1U, APOCALYPSE = 2U };

  CastFromEnum( ) : _value( MyEnumeration::OK )
  {
  }

  CastFromEnum( const MyEnumeration initialValue ) : _value( initialValue )
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
    if ( this->_value == MyEnumeration::OK ) {
      return true;
    } else {
      return false;
    }
  }

private:
  MyEnumeration _value;
};

#endif
