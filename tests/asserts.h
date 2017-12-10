#ifndef TESTS_ASSERT_H_
#define TESTS_ASSERT_H_

#include <cassert>

#define ASSERT_EQ(actual, expected) assert(actual == expected)
#define ASSERT_NEQ(actual, expected) assert(actual != expected)

#define ASSERT_OK(status) status.IsOk()
// TODO: Test for specific statuses
#define ASSERT_NOT_OK(status) (!status.IsOk())

#define ASSERT_VALUE_EQ(statusor, expected) \
  ASSERT_EQ(statusor.ValueOrDie(), expected)
#define ASSERT_VALUE_NEQ(statusor, expected) \
  ASSERT_NEQ(statusor.ValueOrDie(), expected)

#endif  // TESTS_ASSERT_H_
