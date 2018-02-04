#include "catch.hpp"

#include <sstream>
#include <string>

#include "widen_string.h"

#include "common/constants.h"
#include "emulator/memory.h"

using common::Word;
using common::kMemorySize;
using emulator::Memory;
using tests::WidenString;

Memory newMemory(const std::string &program) {
  const std::string &converted_program = WidenString(program);
  std::stringstream program_stream(converted_program);
  return Memory(&program_stream);
}

TEST_CASE("Values can be stored in and loaded from memory objects") {
  Memory mem = newMemory("foo");

  REQUIRE(mem.Load(0).ValueOrDie() == 'f');
  REQUIRE(mem.Load(1).ValueOrDie() == 'o');
  REQUIRE(mem.Load(2).ValueOrDie() == 'o');

  REQUIRE(mem.Store(0, 'c').IsOk());
  REQUIRE(mem.Store(0, 'b').IsOk());
  REQUIRE(mem.Store(1, 'a').IsOk());
  REQUIRE(mem.Store(2, 'r').IsOk());
  REQUIRE(mem.Store(3, 'c').IsOk());
  REQUIRE(mem.Load(0).ValueOrDie() == 'b');
  REQUIRE(mem.Load(1).ValueOrDie() == 'a');
  REQUIRE(mem.Load(2).ValueOrDie() == 'r');
}

TEST_CASE("The instruction pointer can be advanced and read from") {
  Memory mem = newMemory("foo");

  REQUIRE(mem.ReadPointer() == 'f');
  mem.AdvancePointer();
  REQUIRE(mem.ReadPointer() == 'o');
  mem.AdvancePointer();
  REQUIRE(mem.ReadPointer() == 'o');

  REQUIRE(mem.Jump(0).IsOk());
  REQUIRE(mem.ReadPointer() == 'f');
  mem.AdvancePointer();
  REQUIRE(mem.ReadPointer() == 'o');
  mem.AdvancePointer();
  REQUIRE(mem.ReadPointer() == 'o');
}

TEST_CASE("Locations past the bounds of the memory can't be accessed") {
  Memory mem = newMemory("foo");

  // TODO: test for actual error codes
  REQUIRE_FALSE(mem.Load(kMemorySize).IsOk());
  REQUIRE_FALSE(mem.Store(kMemorySize, 'a').IsOk());
  REQUIRE_FALSE(mem.Jump(kMemorySize).IsOk());
}
