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

TEST ( CPP20_FunctionalTests, MultipleSuccessfulPushes ) // NOLINT
{
    // a write phase fills up the complete buffer before a read is requested.
    cpp20_concepts::CircularBuffer<int,3U> b{};
    b.push(1U);
    b.push(2U);
    b.push(3U);
    EXPECT_EQ(1U, b.pop());
    EXPECT_EQ(2U, b.pop());
    EXPECT_EQ(3U, b.pop());
}

TEST ( CPP20_FunctionalTests, BufferOverflow ) // NOLINT
{
    // a write phase fills up the complete buffer before a read is requested.
    cpp20_concepts::CircularBuffer<int,3U> b{};
    b.push(1U);
    b.push(2U);
    b.push(3U);
    b.push(4U);
    cpp20_concepts::CircularBuffer< int, 3U >::ErrorCode
        e = cpp20_concepts::CircularBuffer< int, 3U >::ErrorCode::kFULL;
    EXPECT_EQ ( e, b.getErrorCode ( ) );
    EXPECT_EQ(1U, b.pop());
    EXPECT_EQ(2U, b.pop());
    EXPECT_EQ(3U, b.pop());
}

