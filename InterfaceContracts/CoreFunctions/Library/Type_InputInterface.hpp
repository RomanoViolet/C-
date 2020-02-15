#ifndef TYPE_INPUT_INTERFACE_HPP_
#define TYPE_INPUT_INTERFACE_HPP_

#include <HighAssuranceInterface.hpp>

#include <iostream>

class AbstractInputInterface
{
public:
  virtual ~AbstractInputInterface( ) = default;
};

template < typename T >
class InputInterface : public HighAssuranceInputInterface
{
public:
  enum class ErrorState : short { OK = 0U, ERROR = 1U };
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

  void preprocessInputs( );

private:
  T _thisInterface;
  ErrorState error;
};

#endif  // !TYPE_INPUT_INTERFACE_HPP_
