#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

#include <cstddef>
#include <cstdint>

namespace common {

// TODO: Make these specified as flags during the build
constexpr size_t kMemorySize = 1024;
using Word = int16_t;

}  // namespace common

#endif  // COMMON_CONSTANTS_H_
