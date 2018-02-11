#ifndef EMULATOR_ACCUMULATOR_H_
#define EMULATOR_ACCUMULATOR_H_

#include "common/constants.h"

namespace emulator {

class Accumulator {
 public:
  Accumulator() : Accumulator(0) {}

  explicit Accumulator(const common::Word value) : value_(value) {}

  common::Word Get() const { return value_; }
  void Set(const common::Word value) { value_ = value; }
  void Reset() { value_ = 0; }

  void Add(const common::Word value) { value_ += value; }

  bool IsZero() const { return value_ == 0; }
  bool IsNegative() const { return value_ < 0; }

 private:
  common::Word value_;
};

}  // namespace emulator

#endif  // EMULATOR_ACCUMULATOR_H_
