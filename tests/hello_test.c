#include "unity_fixture.h"

TEST_GROUP(hello);

TEST_SETUP(hello) {

}

TEST_TEAR_DOWN(hello) {

}

TEST(hello, should_say_hello) {
    TEST_ASSERT_EQUAL_STRING("hello", "hello");
}

TEST_GROUP_RUNNER(hello) {
    RUN_TEST_CASE(hello, should_say_hello);
}