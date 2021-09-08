#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "TypeExists.hpp"
namespace cpp20_concepts
{
    TEST ( ClassDeathTest, ZeroCapacityFIFO ) // NOLINT
    {
        static_assert ( ! NonZeroCapacityOfBuffer< int, 0 > ); // NOTLINT
        EXPECT_TRUE ( true );
    }
} // namespace cpp20_concepts

namespace cpp_17
{
    TEST ( ExistenceTests, Exists ) // NOLINT
    {
        bool does_exist = TypeExists<Buffer<int,10>>::value; // NOLINT
        
        EXPECT_TRUE(does_exist);
        //EXPECT_TRUE ( TypeExists<Buffer<int,10>>::value );
    }

    TEST ( ExistenceTests, DoesNotExists ) // NOLINT
    {
        bool does_exist = TypeExists<Buffer<int,0>>::value;
        EXPECT_FALSE ( does_exist );
    }
} // namespace cpp_17
