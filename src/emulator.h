#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <cstddef>
#include <iostream>

#include "accumulator.h"
#include "constants.h"
#include "memory.h"
#include "status.h"

class Emulator {
 public:
  Emulator(const std::istream input, const std::ostream output)
      : input_(input.rdbuf()), output_(output.rdbuf()), is_halted_(false) {}

  Status Load(const size_t operand);
  Status Store(const size_t operand);
  Status Clear();

  Status Add(const size_t operand);

  Status BranchZero(const size_t operand);
  Status BranchNegative(const size_t operand);
  Status BranchUnconditional(const size_t operand);

  Status ReadInput();
  Status WriteOutput();

  Status Halt();
  bool IsHalted() const;

 private:
  Accumulator<Word> acc_;
  Memory<Word, kMemorySize> mem_;
  std::istream input_;
  std::ostream output_;
  bool is_halted_;
};

#endif  // EMULATOR_H_
