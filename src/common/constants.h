#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

#include <cstddef>
#include <cstdint>

#ifndef MEMORY_SIZE
#define MEMORY_SIZE 1024
#endif

#ifndef WORD_SIZE
#define WORD_SIZE 16
#endif

namespace common {

#define WORD_TYPE2(size) int##size##_t
#define WORD_TYPE(size) WORD_TYPE2(size)

constexpr size_t kMemorySize = MEMORY_SIZE;
using Word = WORD_TYPE(WORD_SIZE);

#undef WORD_TYPE
#undef WORD_TYPE2

}  // namespace common

#endif  // COMMON_CONSTANTS_H_
