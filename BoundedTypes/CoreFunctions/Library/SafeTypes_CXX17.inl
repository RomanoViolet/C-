#ifndef SAFETYPES_CXX17_INL_
#define SAFETYPES_CXX17_INL_

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

    // Negative sign from denominator is always moved to the numerator.
    // if constexpr ( DenominatorForMinBound < 0 ) {
    //   NumeratorForMinBound = NumeratorForMinBound * -1;
    //   DenominatorForMinBound = DenominatorForMinBound * -1;
    // }

    constexpr NewFraction minBound = []( ) {
      NewFraction f;
      if ( DenominatorForMinBound < 0 ) {
        f.numerator = NumeratorForMinBound * -1;
        f.denominator = DenominatorForMinBound * -1;

      } else {
        f.numerator = NumeratorForMinBound;
        f.denominator = DenominatorForMinBound;
      }
      return f;
    }( );

    constexpr NewFraction maxBound = []( ) {
      NewFraction f;
      if ( DenominatorForMaxBound < 0 ) {
        f.numerator = NumeratorForMaxBound * -1;
        f.denominator = DenominatorForMaxBound * -1;

      } else {
        f.numerator = NumeratorForMaxBound;
        f.denominator = DenominatorForMaxBound;
      }
      return f;
    }( );

    static_assert( ( ( long long )minBound.numerator * maxBound.denominator )
                       < ( ( long long )minBound.denominator * maxBound.numerator ),
                   "Provided lower bound is greater than the provided upper bound. Abort" );

    // min and max bounds are correct.
    if ( value < _min ) {
      _value = _min;
    } else if ( value > _max ) {
      _value = _max;
    } else {
      _value = value;
    }
  }  // end of constructor

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

}  // namespace RomanoViolet

#endif  //. #ifndef SAFETYPES_CXX17_INL_
