#ifndef SAFETYPES_INL_
#define SAFETYPES_INL_

#include "SafeTypes.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
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

    // verify that min <= max
#if ( __cplusplus == 201703L )
    constexpr auto IsLowerBoundLessThanUpperBound = []( int a, int b, int c, int d ) {
      static_assert( ( a * d ) < ( b * c ),
                     "Provided lower bound is greater than the provided upper bound. Abort" );
    };
    IsLowerBoundLessThanUpperBound( NumeratorForMinBound, DenominatorForMinBound,
                                    NumeratorForMaxBound, DenominatorForMaxBound );
#else
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
