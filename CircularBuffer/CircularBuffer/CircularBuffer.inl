#ifndef CIRCULAR_BUFFER_INL_INCLUDED
#define CIRCULAR_BUFFER_INL_INCLUDED

//#include "CircularBuffer.hpp"
#include <algorithm>

namespace cpp20_concepts
{
    template < typename T, uint8_t C >
    requires NonZeroCapacityOfBuffer< T, C >
    CircularBuffer<T,C>::CircularBuffer ( const T fillValue )
        : insertPoint_ ( C ), extractPoint_ ( C-1 )
    {
        std::fill ( values_.begin ( ), values_.end ( ), fillValue );
        this->e_ = ErrorCode ::kFULL;
    }

    template < typename T, uint8_t C >
    requires NonZeroCapacityOfBuffer< T, C >
    CircularBuffer<T,C>::CircularBuffer ( )
        : insertPoint_ ( 0U ), extractPoint_ ( 0U )
    {
        std::fill ( values_.begin ( ), values_.end ( ), T() );
    }

    template < typename T, uint8_t C >
    requires NonZeroCapacityOfBuffer< T, C >
    auto CircularBuffer<T,C>::pop ( ) -> T
    {
        // Requirement: single read.
        // destructive read.
        // Cases are similar to push().
        // Safety: Write head must never cross the Read head
        //         Therefore, write is refused when read head and write head
        //         are at the same position.
        if ( this->e_ == ErrorCode::kEMPTY ) {
            // error code remains the same
            return T();
        }

        //T value_ = std::get< this->extractPoint_ >;
        T value_ = this->values_[this->extractPoint_];
        this->extractPoint_++;
        // wrap around if necessary
        if ( this->extractPoint_ == this->values_.max_size ( ) ) {
            this->extractPoint_ = 0U;
        }

        if (this->extractPoint_ == this->insertPoint_)
        {
            this->e_ = ErrorCode :: kEMPTY;
        }
        else
        {
            this->e_ = ErrorCode :: kOK;
        }

        
        return ( value_ );
    }

    template < typename T, uint8_t C >
    requires NonZeroCapacityOfBuffer< T, C >
    auto CircularBuffer<T,C>::push ( const T value ) -> void
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
        if (this->e_ == ErrorCode::kFULL) {
            return;
            
        }

        //std::get< this->insertPoint_ > ( this->values_ ) = value;
        this->values_[this->insertPoint_] = value;
        this->insertPoint_++;
        // wrap the insert point if necessary, but do not cross the Read head.
        if ( this->insertPoint_ == this->values_.max_size ( ) ) {
            this->insertPoint_ = 0U;
        }

        if (this->insertPoint_ == this->extractPoint_)
        {
            this->e_ = ErrorCode::kFULL;
        }
        else
        {
            this->e_ = ErrorCode::kOK;
        }

        

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

    template < typename T, uint8_t C >
    requires NonZeroCapacityOfBuffer< T, C >
    auto CircularBuffer<T,C>::getErrorCode() -> typename CircularBuffer<T,C>::ErrorCode const
    {
        return this->e_;
    }
}  // namespace cpp20_concepts

namespace cpp_17
{
    template < typename T, uint8_t C >
    CircularBuffer<T, C,std::enable_if_t< ( C > 0 ) >>::CircularBuffer(): insertPoint_ ( C ), extractPoint_ ( C-1 )
    {
        std::fill ( values_.begin ( ), values_.end ( ), T() );
        this->e_ = ErrorCode :: kFULL;
    }

} // namespace cpp20_concepts


#endif