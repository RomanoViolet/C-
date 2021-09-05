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

auto pop ( ) -> T
{
    // Requirement: single read.
    // destructive read.
    // Cases are similar to push().
    // Safety: Write head must never cross the Read head
    //         Therefore, write is refused when read head and write head
    //         are at the same position.
    if ( this->insertPoint_ == this->extractPoint_ ) {
        this->e_ = ErrorCode::kEMPTY;
        return;
    }

    T value_ = std::get< this->extractPoint_ >;
    this->extractPoint_++;
    // wrap around if necessary
    if ( this->extractPoint_ == this->values_.max_size ( ) ) {
        this->extractPoint_ = 0U;
    }

    this->e_ = ErrorCode : kOK;
    return ( value_ );
}

auto push ( const T value ) -> void
{
    // Requirement: only a single value is inserted at a time
    // insert at write  head
    // Case 1
    // Normal situation before wrap around
    // Safety: Write head must never cross the Read head
    //         Therefore, write is refused when read head and write head
    //         are at the same position.
    //[ |   |   |   |   ]
    //        R       W
    // insert, then move the insert point forward.
    if ( this->insertPoint_ == this->extractPoint_ ) {
        this->e_ = ErrorCode::kFULL;
        return;
    }

    std::get< this->insertPoint_ > ( this->values_ ) = value;
    this->insertPoint_++;
    // wrap the insert point if necessary, but do not cross the Read head.
    if ( this->insertPoint_ == this->values_.max_size ( ) ) {
        this->insertPoint_ = 0U;
    }

    this->e_ = ErrorCode::kOK;

    //
    // Case 2
    // write head wrapped around
    // Safety: Write head must never cross the Read head
    //         Therefore, write is refused when read head and write head
    //         are at the same position.
    //[ |   |   |   |   ]
    //    W       R
    // implementation same as above.
}

#endif
