#ifndef HEADER_HPP_INCLUDED
#define HEADER_HPP_INCLUDED
#include <cstdint>
#include <type_traits>
template < typename T, uint8_t C > class CircularBuffer
{
   public:
    CircularBuffer ( ) = default;
};

template < typename T > class CircularBuffer< T, 0U > : std::false_type
{
};


#endif
