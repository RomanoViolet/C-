#ifndef SAFETYPES_CXX11_HPP_
#define SAFETYPES_CXX11_HPP_

#include <cstdint>
namespace RomanoViolet
{
  // It would be convenient to have a custom type as a template parameter, but see
  // https://stackoverflow.com/q/15896579
  // https://godbolt.org/z/sSCqs7
  template < int NumeratorForMinBound = 1,
             int DenominatorForMinBound = 1,
             int NumeratorForMaxBound = 1,
             int DenominatorForMaxBound = 1 >
  class SafeType
  {
  public:
    SafeType( float value );
    float getMinValue( );
    float getValue( );

    // copy constructor
    SafeType( const SafeType &other );

    // assignment operator
    SafeType &operator=( const SafeType &other );

    // addition operator
    SafeType operator+( const SafeType &other );

    // allows: float x = Object.
    operator float( ) const;

  private:
    float _min;
    float _max;
    float _value;
  };
  template < int NumeratorForMinBound, int NumeratorForMaxBound >
  class SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >
  {
  public:
    SafeType( float value );
    float getValue( );

    // copy constructor
    SafeType( const SafeType &other );

    // assignment operator
    SafeType &operator=( const SafeType &other );

    // allows: float x = Object.
    operator float( ) const;

  private:
    int _min;
    int _max;
    float _value;

    // define temporary data structure to hold new numerators and denominators if these need to be
    // transformed.
  };

#define Fraction( a, b ) a, b

}  // namespace RomanoViolet

#include "SafeTypes_CXX11.inl"

#endif  // !SAFETYPES_CXX11_HPP_
