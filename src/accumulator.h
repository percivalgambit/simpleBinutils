#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

template <class ValueType>
class Accumulator {
 public:
  Accumulator() : value_(0) {}

  ValueType Get() const { return value_; }
  void Set(const ValueType value) { value_ = value; }
  void Reset() { value_ = 0; }

  void Add(const ValueType value) { value_ += value; }

  bool IsZero() const { return value_ == 0; }
  bool IsNegative() const { return value_ < 0; }

 private:
  ValueType value_;
};

#endif  // ACCUMULATOR_H_
