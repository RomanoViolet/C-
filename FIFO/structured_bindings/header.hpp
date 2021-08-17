#ifndef HEADER_HPP_INCLUDED
#define HEADER_HPP_INCLUDED
#include <cstdint>
#include <type_traits>
template < typename T, uint8_t C > class RingBuffer
{
   public:
    explicit RingBuffer ( uint8_t initialFill ) = default;
    {

    };

   protected:
   private:
    const uint8_t capacity_;
};

#endif
