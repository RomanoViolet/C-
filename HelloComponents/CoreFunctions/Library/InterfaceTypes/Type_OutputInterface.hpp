#ifndef TYPE_OUTPUT_INTERFACE_HPP_
#define TYPE_OUTPUT_INTERFACE_HPP_
#include <memory>
template < typename T >
class TypeOutputInterface
{
public:
  TypeOutputInterface( const T value );
  TypeOutputInterface( ) = default;
  T getValue( ) const;
  // operator T *( );
  std::shared_ptr< T > toPtr( );
  void setReference( T &&ref );
  void setValue( const T &value );

protected:
  // T is required to be of bounded type. Need a way to ensure this.

  // likely not required on a per interface basis due to usage of bounded types.
  void doPostConditionCheck( );

private:
  // space for symbol must be allocated externally.
  std::shared_ptr< T > _value = nullptr;

  // true when the initializer value is written at the pointer.
  bool isInitialized = false;
};

#include "Type_OutputInterface.inl"

#endif  // TYPE_OUTPUT_INTERFACE_HPP_
