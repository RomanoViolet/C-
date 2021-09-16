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


TEST ( ExistenceTests, TypeExists ) // NOLINT
{
    bool does_exist = TypeExists<cpp_17::CircularBuffer<int,10>>::value; // NOLINT
    
    EXPECT_TRUE(does_exist);
    //EXPECT_TRUE ( TypeExists<Buffer<int,10>>::value );
}

TEST ( ExistenceTests, TypeDoesNotExist ) // NOLINT
{
    bool does_exist = TypeExists<cpp_17::CircularBuffer<int,0>>::value;
    EXPECT_FALSE ( does_exist );
}


TEST ( CPP20_FunctionalTests, PushToken ) // NOLINT
{
    cpp20_concepts::CircularBuffer<int,10U> b{};
    b.push(1U);
    int v = b.pop();
    EXPECT_EQ(1U, v);
}
