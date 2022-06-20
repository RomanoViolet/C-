#ifndef TYPE_INPUT_INTERFACE_HPP_
#define TYPE_INPUT_INTERFACE_HPP_


  template < typename T >
  class TypeInputInterface
  {
  public:
    TypeInputInterface( const T value ): _value(value){};
    TypeInputInterface(  ){};
    void setValue( const T &value );
    const T &getValue( ) const;

  protected:
    // likely not required on a per interface basis due to usage of bounded types.
    // void doPreconditionCheck( );

  private:
    T _value;
  };


#include "Type_InputInterface.inl"

#endif  // TYPE_INPUT_INTERFACE_HPP_
