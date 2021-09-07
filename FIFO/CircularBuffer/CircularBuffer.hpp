#ifndef CIRCULAR_BUFFER_HPP_INCLUDED
#define CIRCULAR_BUFFER_HPP_INCLUDED

#include <array>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <iostream>
// https://akrzemi1.wordpress.com/2020/01/29/requires-expression/
// https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/
// https://godbolt.org/z/9z83P4a17
//
// https://godbolt.org/z/xrhzEx1ez
// https://stackoverflow.com/a/63952541
// https://godbolt.org/z/a9MTce17E

template < typename T, uint8_t C > concept NonZeroCapacityOfBuffer = C >
0U;

template < typename T, uint8_t C >
requires NonZeroCapacityOfBuffer< T, C >
class CircularBuffer
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

template < typename T, unsigned C, typename Enable = void >
class Buffer
{
public:
    Buffer()
    {
        std::cout << " Not Supported" << std::endl;
    }
};
// https://cpppatterns.com/patterns/class-template-sfinae.html
// https://stackoverflow.com/a/10017728
// notice the partial template specialization.
template < typename T, unsigned C >
class Buffer< T, C, std::enable_if_t< (C > 0)>>
{
    public:
    Buffer()
    {
        std::cout << " Supported" << std::endl;
    }
};

//#include "CircularBuffer.inl"

#endif
