#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

#include "constants.h"

class Accumulator {
 public:
  Accumulator() : value_(0) {}

  Word Get() const { return value_; }
  void Set(const Word value) { value_ = value; }
  void Reset() { value_ = 0; }

  void Add(const Word value) { value_ += value; }

  bool IsZero() const { return value_ == 0; }
  bool IsNegative() const { return value_ < 0; }

 private:
  Word value_;
};

#endif  // ACCUMULATOR_H_
