#ifndef UTIL_FIND_H_
#define UTIL_FIND_H_

#include <cstddef>

#include "util/status.h"
#include "util/statusor.h"

namespace util {

template <size_t N, typename Result, typename Value>
constexpr StatusOr<Result> Find(const Result (&arr)[N],
                                const Value Result::*member,
                                const Value &item) {
  for (const Result &entry : arr) {
    if (entry.*member == item) {
      return entry;
    }
  }
  return Status(Status::Code::kNotFound);
}

template <size_t N, typename Result, typename Value>
constexpr Result FindOrDie(const Result (&arr)[N], const Value Result::*member,
                           const Value &item) {
  return Find<N, Result, Value>(arr, member, item).ValueOrDie();
}

}  // namespace util

#endif  // UTIL_FIND_H_
