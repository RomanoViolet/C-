#ifndef SAFETYPES_INL_
#define SAFETYPES_INL_

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

    // define temporary data structure to hold new numerators and denominators if these need to be
    // transformed.
    struct NewFraction {
      int numerator = 1;
      int denominator = 1;
    };

#if ( __cplusplus == 201703L )
    // Negative sign from denominator is always moved to the numerator.
    if constexpr ( DenominatorForMinBound < 0 ) {
      NumeratorForMinBound = NumeratorForMinBound * -1;
      DenominatorForMinBound = DenominatorForMinBound * -1;
    }

    // verify that min <= max

    constexpr auto IsLowerBoundLessThanUpperBound = []( int a, int b, int c, int d ) {
      static_assert( ( a * d ) < ( b * c ),
                     "Provided lower bound is greater than the provided upper bound. Abort" );
    };
    IsLowerBoundLessThanUpperBound( NumeratorForMinBound, DenominatorForMinBound,
                                    NumeratorForMaxBound, DenominatorForMaxBound );
#else
    // Negative sign from denominator is always moved to the numerator.
    // constexpr NewFraction newMinBound = []( ) {
    //   NewFraction f;
    //   if ( DenominatorForMinBound < 0 ) {
    //     f.numerator = NumeratorForMinBound * -1;
    //     f.denominator = DenominatorForMinBound * -1;
    //   } else {
    //     f.numerator = NumeratorForMinBound;
    //     f.denominator = DenominatorForMinBound;
    //   }
    //   return f;
    // };

    int getnewMinBound = []( int b ) -> int {
      // int f;
      if ( b < 0 ) {
        int f = NumeratorForMinBound * -1;
        return f;

      } else {
        int f = NumeratorForMinBound;
        return f;
      }
      // return f;
    };

    constexpr int newMinBound = getnewMinBound( DenominatorForMinBound );

    // verified that the check is done at compile time only for which long long is acceptable.
    // https://godbolt.org/z/8eJKzR, if it is still alive.
    static_assert( ( ( long long )NumeratorForMinBound * DenominatorForMaxBound )
                       < ( ( long long )DenominatorForMinBound * NumeratorForMaxBound ),
                   "Provided lower bound is greater than the provided upper bound. Abort" );
#endif

    _value = value;
  }

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
  }

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
  }

  template < int NumeratorForMinBound, int NumeratorForMaxBound >
  SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::SafeType( int value )
      : _min( NumeratorForMinBound ), _max( NumeratorForMaxBound )
  {
    _value = value;
  }

  template < int NumeratorForMinBound, int NumeratorForMaxBound >
  int SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::getValue( )
  {
    return this->_value;
  }
}  // namespace RomanoViolet

#endif
