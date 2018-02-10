#include "panic.h"

#include <stdexcept>
#include <string>

namespace util {

void Panic(const std::string &message) { throw std::runtime_error(message); }

}  // namespace util
