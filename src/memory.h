#ifndef MEMORY_H_
#define MEMORY_H_

#include <array>
#include <cstddef>
#include <fstream>

#include "constants.h"
#include "status.h"
#include "statusor.h"

class Memory {
 public:
  Memory(std::ifstream* program);

  StatusOr<Word> Load(const size_t location) const;
  Status Store(const size_t location, const Word value);

  Status Jump(const size_t location);

  Word ReadPointer() const;

  void AdvancePointer();

 private:
  std::array<Word, kMemorySize> data_;
  size_t instruction_pointer_;
};

#endif  // MEMORY_H_
