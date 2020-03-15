#ifndef TYPE_OUTPUT_INTERFACE_HPP_
#define TYPE_OUTPUT_INTERFACE_HPP_

namespace RomanoViolet
{
  template < typename T >
  class TypeOutputInterface
  {
  public:
    TypeOutputInterface( ) = default;
    T getValue( ) const;
    void doPostConditionCheck( );

  private:
    T _value;
  };
}  // namespace RomanoViolet

#include "Type_OutputInterface.inl"

#endif  // TYPE_OUTPUT_INTERFACE_HPP_
