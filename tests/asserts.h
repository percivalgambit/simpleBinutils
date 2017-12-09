#ifndef TESTS_ASSERT_H_
#define TESTS_ASSERT_H_

#include <cassert>

#define ASSERT_EQ(actual, expected) assert(actual == expected)
#define ASSERT_NEQ(actual, expected) assert(actual != expected)

#endif  // TESTS_ASSERT_H_
