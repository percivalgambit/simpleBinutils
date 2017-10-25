#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <cstddef>
#include <iostream>

#include "accumulator.h"
#include "memory.h"
#include "status.h"

class Emulator {
 public:
  Emulator(Accumulator acc, Memory mem, std::istream* input,
           std::ostream* output);

  Status Run();

 private:
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
  Accumulator acc_;
  Memory mem_;
  std::istream input_;
  std::ostream output_;
  bool is_halted_;
};

#endif  // EMULATOR_H_
