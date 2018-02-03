#include "emulator/accumulator.h"

#include "asserts.h"

using emulator::Accumulator;

void TestGet();
void TestSet();
void TestReset();
void TestAdd();
void TestIsZero();
void TestIsNegative();

int main() {
  TestGet();
  TestSet();
  TestReset();
  TestAdd();
  TestIsZero();
  TestIsNegative();

  return 0;
}

void TestGet() {
  Accumulator default_acc;
  ASSERT_EQ(default_acc.Get(), 0);

  Accumulator acc(3);
  ASSERT_EQ(acc.Get(), 3);
}

void TestSet() {
  Accumulator acc;
  acc.Set(4);
  ASSERT_EQ(acc.Get(), 4);
}

void TestReset() {
  Accumulator acc(3);
  acc.Reset();
  ASSERT_EQ(acc.Get(), 0);
}

void TestAdd() {
  Accumulator acc(2);
  acc.Add(4);
  ASSERT_EQ(acc.Get(), 6);
}

void TestIsZero() {
  Accumulator zero_acc(0);
  assert(zero_acc.IsZero());

  Accumulator nonzero_acc(3);
  assert(!nonzero_acc.IsZero());
}

void TestIsNegative() {
  Accumulator positive_acc(3);
  assert(!positive_acc.IsNegative());

  Accumulator negative_acc(-3);
  assert(negative_acc.IsNegative());
}
