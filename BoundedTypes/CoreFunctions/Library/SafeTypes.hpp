#ifndef SAFETYPES_HPP_
#define SAFETYPES_HPP_

#include <cstdint>
namespace RomanoViolet
{
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
  };

#define Fraction( a, b ) a, b
}  // namespace RomanoViolet
#include "SafeTypes.inl"
#endif  // !SAFETYPES_HPP_
