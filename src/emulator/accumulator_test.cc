#include "emulator/accumulator.h"

#include "test_util/catch.hpp"

using emulator::Accumulator;

TEST_CASE("Accumulators can store values") {
  Accumulator acc;
  REQUIRE(acc.Get() == 0);

  acc.Set(3);
  REQUIRE(acc.Get() == 3);

  acc.Add(4);
  REQUIRE(acc.Get() == 7);

  acc.Reset();
  REQUIRE(acc.Get() == 0);
}

TEST_CASE("Values in accumulators can be tested") {
  Accumulator zero_acc;
  REQUIRE(zero_acc.IsZero());
  REQUIRE_FALSE(zero_acc.IsNegative());

  Accumulator positive_acc(3);
  REQUIRE_FALSE(positive_acc.IsZero());
  REQUIRE_FALSE(positive_acc.IsNegative());

  Accumulator negative_acc(-1);
  REQUIRE_FALSE(negative_acc.IsZero());
  REQUIRE(negative_acc.IsNegative());
}
