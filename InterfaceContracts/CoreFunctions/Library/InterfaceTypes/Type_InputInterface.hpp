#ifndef TYPE_INPUT_INTERFACE_HPP_
#define TYPE_INPUT_INTERFACE_HPP_

namespace RomanoViolet
{
  template < typename T >
  class TypeInputInterface
  {
  public:
    TypeInputInterface( ) = default;
    void setValue( const T &value );
    T getValue( ) const;

  private:
    T _value;
  };
}  // namespace RomanoViolet

#endif  // TYPE_INPUT_INTERFACE_HPP_
