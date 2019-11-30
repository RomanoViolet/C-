#ifndef SAFETYPES_HPP_
#define SAFETYPES_HPP_

#include <cstdint>
namespace RomanoViolet
{
  // It would be convenient to have a custom type as a template parameter, but see
  // https://stackoverflow.com/q/15896579
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

  private:
    float _min;
    float _max;
    float _value;

#if ( __cplusplus == 201402L )
    struct NewFraction {
      int numerator = 1;
      int denominator = 1;
    };
    // the compiler treats arguments are runtime changeable, therefore not allowed inside a
    // constexpr.
    //
    // constexpr NewFraction correctBound(
    // const int Numerator,
    // const int Denominator
    //    ) const;
    //
    constexpr NewFraction correctMinBound( ) const;
    constexpr NewFraction correctMaxBound( ) const;

#endif
  };
  template < int NumeratorForMinBound, int NumeratorForMaxBound >
  class SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >
  {
  public:
    SafeType( int value );
    int getValue( );

  private:
    int _min;
    int _max;
    int _value;

    // define temporary data structure to hold new numerators and denominators if these need to be
    // transformed.
#if ( __cplusplus == 201402L )
    struct NewFraction {
      int numerator = 1;
      int denominator = 1;
    };

    constexpr NewFraction correctBound( int Numerator, int Denominator ) const;

#endif
  };

#define Fraction( a, b ) a, b

}  // namespace RomanoViolet

#include "SafeTypes.inl"

#endif  // !SAFETYPES_HPP_
