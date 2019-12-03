#ifndef SAFETYPES__CXX14_INL_
#define SAFETYPES__CXX14_INL_

#include "SafeTypes.hpp"
#include <cassert>
#include <cmath>
#include <limits>
// Reading:
// https://www.boost.org/doc/libs/1_61_0/libs/math/doc/html/math_toolkit/float_comparison.html

// For intellisense. The file will not get included twice.
#include "SafeTypes.hpp"

namespace RomanoViolet
{
  template < int NumeratorForMinBound,
             int DenominatorForMinBound,
             int NumeratorForMaxBound,
             int DenominatorForMaxBound >
  SafeType< NumeratorForMinBound,
            DenominatorForMinBound,
            NumeratorForMaxBound,
            DenominatorForMaxBound >::SafeType( float value )
      : _min( NumeratorForMinBound / ( DenominatorForMinBound * 1.0F ) )
      , _max( NumeratorForMaxBound / ( DenominatorForMaxBound * 1.0F ) )
  {
    // assert that denominators are not zero.
    static_assert( DenominatorForMinBound != 0, "Denominator for lower bound cannot be zero." );
    static_assert( DenominatorForMaxBound != 0, "Denominator for upper bound cannot be zero." );
    static_assert( DenominatorForMinBound > std::numeric_limits< int >::min( ),
                   "Minimum value of denominator is std::numeric_limits<int>::min() + 1" );
    static_assert( DenominatorForMaxBound > std::numeric_limits< int >::min( ),
                   "Minimum value of denominator is std::numeric_limits<int>::min() + 1" );

    // https://godbolt.org/z/RmA4hk
    NewFraction newMinBound = correctMinBound( );

    NewFraction newMaxBound = correctMaxBound( );
    // Although we are using runtime version of assert, the compiler is performing compile-time
    // check. See https://godbolt.org/z/RmA4hk
    assert( ( ( long long )newMinBound.numerator * newMaxBound.denominator )
                < ( ( long long )newMinBound.denominator * newMaxBound.numerator )
            && "Provided lower bound is greater than the provided upper bound. Abort" );

    // min and max bounds are correct.
    if ( value < _min ) {
      _value = _min;
    } else if ( value > _max ) {
      _value = _max;
    } else {
      _value = value;
    }
  }
}  // namespace RomanoViolet

template < int NumeratorForMinBound,
           int DenominatorForMinBound,
           int NumeratorForMaxBound,
           int DenominatorForMaxBound >
float SafeType< NumeratorForMinBound,
                DenominatorForMinBound,
                NumeratorForMaxBound,
                DenominatorForMaxBound >::getMinValue( )
{
  return this->_min;
}  // getMinValue

template < int NumeratorForMinBound,
           int DenominatorForMinBound,
           int NumeratorForMaxBound,
           int DenominatorForMaxBound >
float SafeType< NumeratorForMinBound,
                DenominatorForMinBound,
                NumeratorForMaxBound,
                DenominatorForMaxBound >::getValue( )
{
  return this->_value;
}  // getValue

template < int NumeratorForMinBound, int NumeratorForMaxBound >
SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::SafeType( float value )
    : _min( NumeratorForMinBound ), _max( NumeratorForMaxBound )
{
  _value = value;
}  // constructor

template < int NumeratorForMinBound, int NumeratorForMaxBound >
float SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::getValue( )
{
  return this->_value;
}  // getValue

template < int NumeratorForMinBound,
           int DenominatorForMinBound,
           int NumeratorForMaxBound,
           int DenominatorForMaxBound >
constexpr
    typename SafeType< NumeratorForMinBound,
                       DenominatorForMinBound,
                       NumeratorForMaxBound,
                       DenominatorForMaxBound >::NewFraction SafeType< NumeratorForMinBound,
                                                                       DenominatorForMinBound,
                                                                       NumeratorForMaxBound,
                                                                       DenominatorForMaxBound >::
        correctMinBound(
            // the compiler treats arguments are runtime changeable, therefore not allowed inside
            // a constexpr. const int Numerator, const int Denominator
            ) const
{
  // the statement below is not allowed to be inside a constexpr until C++14.
  NewFraction f;
  if ( DenominatorForMinBound < 0 ) {
    f.denominator = DenominatorForMinBound * -1;
    f.numerator = NumeratorForMinBound * -1;
  } else {
    f.denominator = DenominatorForMinBound;
    f.numerator = NumeratorForMinBound;
  }
  return f;

}  // correctMinBound

template < int NumeratorForMinBound,
           int DenominatorForMinBound,
           int NumeratorForMaxBound,
           int DenominatorForMaxBound >
constexpr
    typename SafeType< NumeratorForMinBound,
                       DenominatorForMinBound,
                       NumeratorForMaxBound,
                       DenominatorForMaxBound >::NewFraction SafeType< NumeratorForMinBound,
                                                                       DenominatorForMinBound,
                                                                       NumeratorForMaxBound,
                                                                       DenominatorForMaxBound >::
        correctMaxBound(
            // the compiler treats arguments are runtime changeable, therefore not allowed inside
            // a constexpr. const int Numerator, const int Denominator
            ) const
{
  // the statement below is not allowed to be inside a constexpr until C++14.
  NewFraction f;
  if ( DenominatorForMaxBound < 0 ) {
    f.denominator = DenominatorForMaxBound * -1;
    f.numerator = NumeratorForMaxBound * -1;
  } else {
    f.denominator = DenominatorForMaxBound;
    f.numerator = NumeratorForMaxBound;
  }
  return f;

}  // correctMaxBound
}  // namespace RomanoViolet

#endif  //. #ifndef SAFETYPES__CXX14_INL_
