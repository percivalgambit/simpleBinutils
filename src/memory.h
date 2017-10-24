#ifndef MEMORY_H_
#define MEMORY_H_

#include <array>
#include <cstddef>

#include "status.h"
#include "statusor.h"

template <class T, size_t Size>
class Memory {
 public:
  StatusOr<T> Load(const size_t location) const {
    return location < Size ? StatusOr<T>(data_[location])
                           : Status(Status::Code::kOutOfBounds);
  }
  Status Store(const size_t location, const T value) {
    if (location >= Size) {
      return Status(Status::Code::kOutOfBounds);
    }
    data_[location] = value;
    return Status::OK;
  }

  Status Jump(const size_t location) {
    if (location >= Size) {
      return Status(Status::Code::kOutOfBounds);
    }
    instruction_pointer_ = location;
    return Status::OK;
  }

  T ReadPointer() const { return data_[instruction_pointer_]; }

  void AdvancePointer() {
    ++instruction_pointer_;
    if (instruction_pointer_ == Size) {
      instruction_pointer_ = 0;
    }
  }

 private:
  std::array<T, Size> data_;
  size_t instruction_pointer_;
};

#endif  // MEMORY_H_
