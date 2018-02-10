#ifndef UTIL_PANIC_H_
#define UTIL_PANIC_H_

#include <string>

namespace util {

[[noreturn]] void Panic(const std::string &message);

}  // namespace util

#endif  // UTIL_PANIC_H_
