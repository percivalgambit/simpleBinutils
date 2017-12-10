#ifndef EMULATOR_MEMORY_H_
#define EMULATOR_MEMORY_H_

#include <array>
#include <cstddef>
#include <istream>

#include "common/constants.h"
#include "util/status.h"
#include "util/statusor.h"

namespace emulator {

class Memory {
 public:
  Memory(std::basic_istream<common::Word>* program);

  util::StatusOr<common::Word> Load(const size_t location) const;
  util::Status Store(const size_t location, const common::Word value);

  util::Status Jump(const size_t location);

  common::Word ReadPointer() const;

  void AdvancePointer();

 private:
  std::array<common::Word, common::kMemorySize> data_;
  size_t instruction_pointer_;
};

}  // namespace emulator

#endif  // EMULATOR_MEMORY_H_
