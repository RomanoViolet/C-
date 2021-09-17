#ifndef CIRCULAR_BUFFER_HPP_INCLUDED
#define CIRCULAR_BUFFER_HPP_INCLUDED

#include <array>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace cpp20_concepts
{
    template < typename T, uint8_t C >
    class CircularBuffer
    {
       public:
        enum class ErrorCode : uint8_t { kOK = 0U, kFULL = 1U, kEMPTY = 2U };
        explicit CircularBuffer ( T fillValue );
        explicit CircularBuffer ( );
        auto pop ( ) -> T;
        auto push ( T value ) -> void;

       protected:
       private:
        std::array< T, C > values_ { };
        uint8_t insertPoint_ { };
        uint8_t extractPoint_ { };
        ErrorCode e_ { ErrorCode::kOK };
    };
}  // namespace cpp20_concepts

namespace cpp_17
{
    //template < typename T, unsigned C, typename Enable = void >
    template < typename T, unsigned C, typename = void >
    class CircularBuffer;
    // https://cpppatterns.com/patterns/class-template-sfinae.html
    // https://stackoverflow.com/a/10017728
    // https://godbolt.org/z/KcerdTeo8
    // notice the partial template specialization.
    template < typename T, unsigned C >
    class CircularBuffer< T, C, std::enable_if_t< ( C > 0 ) > >
    {
       public:
        enum class ErrorCode : uint8_t { kOK = 0U, kFULL = 1U, kEMPTY = 2U };
        explicit CircularBuffer ( T fillValue );
        CircularBuffer ( ) = default;
        auto pop ( ) -> T;
        auto push ( T value ) -> void;

       protected:
       private:
        std::array< T, C > values_ { };
        uint8_t insertPoint_ { };
        uint8_t extractPoint_ { };
        ErrorCode e_ { ErrorCode::OK };
    };
}  // namespace cpp_17


#include "CircularBuffer.inl"

#endif

// Next: detect if a type exists
// https://en.cppreference.com/w/cpp/types/void_t
// https://devblogs.microsoft.com/oldnewthing/20190710-00/?p=102678
// https://godbolt.org/z/fPaezKTvP
// https://stackoverflow.com/a/27688405
