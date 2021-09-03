#ifndef CIRCULAR_BUFFER_INL_INCLUDED
#define CIRCULAR_BUFFER_INL_INCLUDED

#include "CircularBuffer.hpp"

#include <algorithm>

template < typename T, uint8_t C >
requires NonZeroCapacityOfBuffer< T, C >
CircularBuffer::CircularBuffer ( const T fillValue )
    : capacity_ ( C ), insertPoint_ ( 0U ), extractPoint_ ( 0U )
{
    std::fill ( values_.begin ( ), values_.end ( ), fillValue );
}

template < typename T, uint8_t C >
requires NonZeroCapacityOfBuffer< T, C > CircularBuffer::CircularBuffer ( )
    : capacity_ ( C ), insertPoint_ ( 0U ), extractPoint_ ( 0U )
{
}

auto pop ( uint8_t n = 1 ) -> void
{
}

auto push ( const T value ) -> void
{
}

#endif
