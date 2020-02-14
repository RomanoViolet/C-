#ifndef TYPE_INPUT_INTERFACE_HPP_
#define TYPE_INPUT_INTERFACE_HPP_

#include <iostream>

class AbstractInputInterface
{
public:
  virtual ~AbstractInputInterface( ) = default;
};

template < typename T >
class InputInterface : public AbstractInputInterface
{
public:
  InputInterface( ) : _thisInterface( T( ) )
  {
  }

  void setValue( const T a )
  {
    _thisInterface = a;
  }

  const T getValue( ) const
  {
    return _thisInterface;
  }

private:
  T _thisInterface;
};

#endif  // !TYPE_INPUT_INTERFACE_HPP_
