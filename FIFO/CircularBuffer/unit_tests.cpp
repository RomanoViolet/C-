#include "CircularBuffer.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "TypeExists.hpp"

TEST ( ClassDeathTest, ZeroCapacityFIFO ) // NOLINT
{
    static_assert ( ! cpp20_concepts::NonZeroCapacityOfBuffer< int, 0 > ); // NOTLINT
    EXPECT_TRUE ( true );
}


TEST ( ExistenceTests, Exists ) // NOLINT
{
    bool does_exist = TypeExists<cpp_17::Buffer<int,10>>::value; // NOLINT
    
    EXPECT_TRUE(does_exist);
    //EXPECT_TRUE ( TypeExists<Buffer<int,10>>::value );
}

TEST ( ExistenceTests, DoesNotExists ) // NOLINT
{
    bool does_exist = TypeExists<cpp_17::Buffer<int,0>>::value;
    EXPECT_FALSE ( does_exist );
}

