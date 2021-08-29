#ifndef HEADER_HPP_INCLUDED
#define HEADER_HPP_INCLUDED
#include <cstdint>
#include <type_traits>
// https://akrzemi1.wordpress.com/2020/01/29/requires-expression/
// https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/
// https://godbolt.org/z/9z83P4a17
template < typename T, uint8_t C > class CircularBuffer
{
   public:
    CircularBuffer ( ) = default;
};

template < typename T > class CircularBuffer< T, 0U > : std::false_type
{
};


#endif
