#ifndef CIRCULAR_BUFFER_HPP_INCLUDED
#define CIRCULAR_BUFFER_HPP_INCLUDED
#include <concepts>
#include <cstdint>
#include <type_traits>
// https://akrzemi1.wordpress.com/2020/01/29/requires-expression/
// https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/
// https://godbolt.org/z/9z83P4a17
//
// https://godbolt.org/z/xrhzEx1ez
// https://stackoverflow.com/a/63952541
// https://godbolt.org/z/a9MTce17E

template < typename T, uint8_t C >
concept NonZeroCapacityOfBuffer = C >
0U;

template < typename T, uint8_t C >
requires NonZeroCapacityOfBuffer< T, C >
class CircularBuffer
{
   public:
    CircularBuffer ( T fillValue );
    CircularBuffer ( ) = default;
    auto pop ( uint8_t n = 1 ) -> void;
    auto push ( const T value ) -> void;

   protected:
   private:
    uint8_t _capacity { C };
    T _values[ C ] { };
    uint8_t _insertPoint;
    uint8_t _extractPoint;
};

#include "CircularBuffer.inl"

#endif
