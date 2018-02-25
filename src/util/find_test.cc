#include "util/find.h"

#include <stdexcept>

#include "test_util/catch.hpp"

using util::Find;
using util::FindOrDie;

struct Struct {
  int a;
  bool b;

  bool operator==(const Struct &other) const {
    return this->a == other.a && this->b == other.b;
  }
};

constexpr Struct s1 = {1, true};
constexpr Struct s2 = {2, false};
constexpr Struct list[] = {s1, s2};

TEST_CASE("Find can find objects in arrays") {
  REQUIRE(Find(list, &Struct::a, 2).ValueOrDie() == s2);
  REQUIRE(FindOrDie(list, &Struct::a, 2) == s2);

  REQUIRE_FALSE(Find(list, &Struct::a, 3).IsOk());
  REQUIRE_THROWS_AS(FindOrDie(list, &Struct::a, 3), std::runtime_error);
}
