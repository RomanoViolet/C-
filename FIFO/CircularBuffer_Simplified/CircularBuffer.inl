#ifndef CIRCULAR_BUFFER_INL_INCLUDED
#define CIRCULAR_BUFFER_INL_INCLUDED


#include <algorithm>
#include "CircularBuffer.hpp"

namespace cpp20_concepts
{
    template < typename T, uint8_t C >
    CircularBuffer<T,C>::CircularBuffer ( const T fillValue )

    {
        std::fill ( values_.begin ( ), values_.end ( ), fillValue );
    }

    template < typename T, uint8_t C >
    CircularBuffer<T,C>::CircularBuffer ( )

    {
        std::fill ( values_.begin ( ), values_.end ( ), T() );
    }

    template < typename T, uint8_t C >
    auto CircularBuffer<T,C>::pop ( ) -> T
    {
        if ( this->insertPoint_ == this->extractPoint_ ) {
            this->e_ = ErrorCode::kEMPTY;
            return T();
        }

        //T value = std::get< this->extractPoint_ >(this->values_);
        T value = this->values_[this->extractPoint_];
        this->extractPoint_++;

        if ( this->extractPoint_ == this->values_.max_size ( ) ) {
            this->extractPoint_ = 0U;
        }

        this->e_ = ErrorCode :: kOK;
        return ( value );
    }

    template < typename T, uint8_t C >
    auto CircularBuffer<T,C>::push ( const T value ) -> void
    {
        if ( this->insertPoint_ == this->extractPoint_ ) {
            this->e_ = ErrorCode::kFULL;
            return;
        }

        //std::get< this->insertPoint_ > ( this->values_ ) = value;
        this->values_[this->insertPoint_] = value;
        this->insertPoint_++;
    
        if ( this->insertPoint_ == this->values_.max_size ( ) ) {
            this->insertPoint_ = 0U;
        }

        this->e_ = ErrorCode::kOK;
    }
}  // namespace cpp20_concepts


#endif
