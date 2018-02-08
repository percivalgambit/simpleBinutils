#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "word_stream.h"

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/accumulator.h"
#include "emulator/emulator.h"

using common::Instruction;
using common::Word;
using emulator::Accumulator;
using emulator::Emulator;
using test::WordStream;

TEST_CASE("An emulator can read and write characters") {
  std::stringstream input;
  std::stringstream output;
  WordStream program("foo");
  Emulator emu(&program, &input, &output, Accumulator('b'));

  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(output.str() == "b");
  input << 'c';
  REQUIRE(emu.ReadInput().IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(output.str() == "bc");
}

TEST_CASE("An emulator can load and store values in memory") {
  std::istringstream input;
  std::ostringstream output;
  WordStream program("foobar");
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Load(3).IsOk());
  REQUIRE(emu.Store(0).IsOk());
  REQUIRE(emu.Load(4).IsOk());
  REQUIRE(emu.Store(1).IsOk());
  REQUIRE(emu.Load(5).IsOk());
  REQUIRE(emu.Store(2).IsOk());

  REQUIRE(emu.Load(0).IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(emu.Load(1).IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(emu.Load(2).IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(output.str() == "bar");
}

TEST_CASE("An emulator has an accumulator that can be manipulated") {
  std::stringstream input;
  std::stringstream output;
  WordStream program("!");
  Emulator emu(&program, &input, &output, Accumulator('0'));

  REQUIRE(emu.Add(0).IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(output.str() == "Q");

  output.str("");
  REQUIRE(emu.Clear().IsOk());
  REQUIRE(emu.WriteOutput().IsOk());
  REQUIRE(output.get() == '\0');
}

TEST_CASE("An emulator has a pointer that can jump") {
  std::istringstream input;
  std::ostringstream output;
  WordStream program("bar");
  Emulator emu(&program, &input, &output, Accumulator(0));

  REQUIRE(emu.BranchZero(2).IsOk());
  REQUIRE(emu.ReadPointer() == 'r');
  REQUIRE(emu.BranchNegative(1).IsOk());
  REQUIRE(emu.ReadPointer() == 'r');
  REQUIRE(emu.BranchUnconditional(0).IsOk());
  REQUIRE(emu.ReadPointer() == 'b');

  program = WordStream("bar");
  emu = Emulator(&program, &input, &output, Accumulator(-1));
  REQUIRE(emu.BranchZero(2).IsOk());
  REQUIRE(emu.ReadPointer() == 'b');
  REQUIRE(emu.BranchNegative(1).IsOk());
  REQUIRE(emu.ReadPointer() == 'a');
  REQUIRE(emu.BranchUnconditional(0).IsOk());
  REQUIRE(emu.ReadPointer() == 'b');
}

TEST_CASE("An emulator can halt") {
  WordStream program("foo");
  Emulator emu(&program);

  REQUIRE(emu.Halt().IsOk());
  REQUIRE(emu.IsHalted());

  // TODO: fix this
  /*
  SECTION("Operations will fail when the emulator is halted") {
    REQUIRE_FALSE(emu.Load(0).IsOk());
    REQUIRE_FALSE(emu.Store(0).IsOk());
    REQUIRE_FALSE(emu.Clear().IsOk());
    REQUIRE_FALSE(emu.Add(0).IsOk());
    REQUIRE_FALSE(emu.BranchZero(0).IsOk());
    REQUIRE_FALSE(emu.BranchNegative(0).IsOk());
    REQUIRE_FALSE(emu.BranchUnconditional(0).IsOk());
    REQUIRE_FALSE(emu.ReadInput().IsOk());
    REQUIRE_FALSE(emu.WriteOutput().IsOk());
    REQUIRE_FALSE(emu.Halt().IsOk());
  } */
}

TEST_CASE("An emulator can run a program") {
  std::istringstream input;
  std::stringstream output;
  WordStream program(std::vector<Word>({Word(Instruction::Code::LOD),
                                        16,
                                        Word(Instruction::Code::OUT),
                                        Word(Instruction::Code::LOD),
                                        17,
                                        Word(Instruction::Code::OUT),
                                        Word(Instruction::Code::LOD),
                                        18,
                                        Word(Instruction::Code::OUT),
                                        Word(Instruction::Code::LOD),
                                        19,
                                        Word(Instruction::Code::OUT),
                                        Word(Instruction::Code::LOD),
                                        20,
                                        Word(Instruction::Code::OUT),
                                        Word(Instruction::Code::HLT),
                                        'h',
                                        'e',
                                        'l',
                                        'l',
                                        'o'}));
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "hello");
}
