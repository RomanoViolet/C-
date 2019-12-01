#ifndef SAFETYPES_CXX11_INL_
#define SAFETYPES_CXX11_INL_

#include "SafeTypes.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
// Reading:
// https://www.boost.org/doc/libs/1_61_0/libs/math/doc/html/math_toolkit/float_comparison.html

// For intellisense. The file will not get included twice.
//
// static_assert seems to be moved out of the conditional scope by the compiler. Therefore,
// assert(...) is used instead.
//
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

    if ( ( DenominatorForMinBound < 0 ) && ( DenominatorForMaxBound < 0 ) ) {
      constexpr int newNumeratorForMinBound = -NumeratorForMinBound;
      constexpr int newDenominatorForMinBound = -DenominatorForMinBound;
      constexpr int newNumeratorForMaxBound = -NumeratorForMaxBound;
      constexpr int newDenominatorForMaxBound = -DenominatorForMaxBound;
      assert( ( ( long long )newNumeratorForMinBound * newDenominatorForMaxBound )
                  < ( ( long long )newDenominatorForMinBound * newNumeratorForMaxBound )
              && "Provided lower bound is greater than the provided upper bound. Abort" );
    } else if ( ( DenominatorForMinBound < 0 ) && ( DenominatorForMaxBound > 0 ) ) {
      constexpr int newNumeratorForMinBound = -NumeratorForMinBound;
      constexpr int newDenominatorForMinBound = -DenominatorForMinBound;
      constexpr int newNumeratorForMaxBound = NumeratorForMaxBound;
      constexpr int newDenominatorForMaxBound = DenominatorForMaxBound;
      assert( ( ( long long )newNumeratorForMinBound * newDenominatorForMaxBound )
                  < ( ( long long )newDenominatorForMinBound * newNumeratorForMaxBound )
              && "Provided lower bound is greater than the provided upper bound. Abort" );
    } else if ( ( DenominatorForMinBound > 0 ) && ( DenominatorForMaxBound < 0 ) ) {
      constexpr int newNumeratorForMinBound = NumeratorForMinBound;
      constexpr int newDenominatorForMinBound = DenominatorForMinBound;
      constexpr int newNumeratorForMaxBound = -NumeratorForMaxBound;
      constexpr int newDenominatorForMaxBound = -DenominatorForMaxBound;
      assert( ( ( long long )newNumeratorForMinBound * newDenominatorForMaxBound )
                  < ( ( long long )newDenominatorForMinBound * newNumeratorForMaxBound )
              && "Provided lower bound is greater than the provided upper bound. Abort" );
    } else
    // DenominatorForMinBound > 0 && DenominatorForMaxBound > 0 )
    {
      constexpr int newNumeratorForMinBound = NumeratorForMinBound;
      constexpr int newDenominatorForMinBound = DenominatorForMinBound;
      constexpr int newNumeratorForMaxBound = NumeratorForMaxBound;
      constexpr int newDenominatorForMaxBound = DenominatorForMaxBound;
      assert( ( ( long long )newNumeratorForMinBound * newDenominatorForMaxBound )
                  < ( ( long long )newDenominatorForMinBound * newNumeratorForMaxBound )
              && "Provided lower bound is greater than the provided upper bound. Abort" );
    }

    _value = value;
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
  SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::SafeType( int value )
      : _min( NumeratorForMinBound ), _max( NumeratorForMaxBound )
  {
    _value = value;
  }  // constructor

  template < int NumeratorForMinBound, int NumeratorForMaxBound >
  int SafeType< NumeratorForMinBound, 1, NumeratorForMaxBound, 1 >::getValue( )
  {
    return this->_value;
  }  // getValue
}  // namespace RomanoViolet

#endif  //. #ifndef SAFETYPES_CXX11_INL_
