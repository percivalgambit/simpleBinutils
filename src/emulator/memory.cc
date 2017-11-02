#include "emulator/memory.h"

#include <cstddef>
#include <fstream>

#include "common/constants.h"
#include "util/status.h"
#include "util/statusor.h"

using common::kMemorySize;
using common::Word;
using util::Status;
using util::StatusOr;

namespace emulator {

Memory::Memory(std::ifstream* program) : instruction_pointer_(0) {
  program->read(reinterpret_cast<char*>(data_.data()), kMemorySize);
}

StatusOr<Word> Memory::Load(const size_t location) const {
  return location < kMemorySize ? StatusOr<Word>(data_[location])
                                : Status(Status::Code::kOutOfBounds);
}

Status Memory::Store(const size_t location, const Word value) {
  if (location >= kMemorySize) {
    return Status(Status::Code::kOutOfBounds);
  }
  data_[location] = value;
  return Status::OK;
}

Status Memory::Jump(const size_t location) {
  if (location >= kMemorySize) {
    return Status(Status::Code::kOutOfBounds);
  }
  instruction_pointer_ = location;
  return Status::OK;
}

Word Memory::ReadPointer() const { return data_[instruction_pointer_]; }

void Memory::AdvancePointer() {
  ++instruction_pointer_;
  if (instruction_pointer_ == kMemorySize) {
    instruction_pointer_ = 0;
  }
}

}  // namespace emulator
