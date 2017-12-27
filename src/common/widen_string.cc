#include "widen_string.h"

#include <string>

#include "common/constants.h"

namespace common {

std::string WidenString(const std::string& str) {
  const std::basic_string<Word> wide_str(str.cbegin(), str.cend());
  return std::string((char*)wide_str.data(), str.size() * sizeof(Word));
}

}  // namespace common
