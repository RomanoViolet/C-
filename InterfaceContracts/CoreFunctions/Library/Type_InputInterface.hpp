#ifndef TYPE_INPUT_INTERFACE_HPP_
#define TYPE_INPUT_INTERFACE_HPP_

#include <iostream>

template < typename T >
class InputInterface final
{
public:
  InputInterface( ) : _thisInterface( T( ) )
  {
  }

  void setValue( const T a )
  {
    _thisInterface = a;
  };

private:
  T _thisInterface;
};

#endif  // !TYPE_INPUT_INTERFACE_HPP_
