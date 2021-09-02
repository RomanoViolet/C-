#ifndef CIRCULAR_BUFFER_INL_INCLUDED
#define CIRCULAR_BUFFER_INL_INCLUDED

#include "CircularBuffer.hpp"


template < typename T, uint8_t C >
requires NonZeroCapacityOfBuffer< T, C >
CircularBuffer::CircularBuffer ( T fillValue )
{
    //
}

#endif
