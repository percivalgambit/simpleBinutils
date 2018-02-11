#ifndef EMULATOR_EMULATOR_H_
#define EMULATOR_EMULATOR_H_

#include <cstddef>
#include <iostream>

#include "common/constants.h"
#include "emulator/accumulator.h"
#include "emulator/memory.h"
#include "util/status.h"

namespace emulator {

class Emulator {
 public:
  explicit Emulator(std::istream* program);

  Emulator(std::istream* program, std::istream* input, std::ostream* output,
           const Accumulator acc);

  util::Status Run();

 private:
  util::Status Load(const size_t operand);
  util::Status Store(const size_t operand);
  util::Status Clear();

  util::Status Add(const size_t operand);

  util::Status BranchZero(const size_t operand);
  util::Status BranchNegative(const size_t operand);
  util::Status BranchUnconditional(const size_t operand);

  util::Status ReadInput();
  util::Status WriteOutput();

  util::Status Halt();
  bool IsHalted() const;

  common::Word ReadPointer() const;

  Accumulator acc_;
  Memory mem_;
  std::istream* input_;
  std::ostream* output_;
  bool is_halted_;
};

}  // namespace emulator

#endif  // EMULATOR_EMULATOR_H_
