#include "emulator/emulator.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/accumulator.h"
#include "test_util/catch.hpp"
#include "test_util/word_stream.h"

using common::Instruction;
using common::Word;
using emulator::Accumulator;
using emulator::Emulator;
using test_util::WordStream;

TEST_CASE("An emulator can read and write characters") {
  std::stringstream input;
  std::stringstream output;
  WordStream program(
      std::vector<Word>{static_cast<Word>(Instruction::Code::OUT),
                        static_cast<Word>(Instruction::Code::INP),
                        static_cast<Word>(Instruction::Code::OUT),
                        static_cast<Word>(Instruction::Code::HLT)});
  Emulator emu(&program, &input, &output, Accumulator('b'));

  input << 'c';
  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "bc");
}

TEST_CASE("An emulator can load and store values in memory") {
  std::istringstream input;
  std::ostringstream output;
  WordStream program(std::vector<Word>{
      static_cast<Word>(Instruction::Code::LOD), 17,
      static_cast<Word>(Instruction::Code::STO), 15,
      static_cast<Word>(Instruction::Code::LOD), 18,
      static_cast<Word>(Instruction::Code::STO), 16,
      static_cast<Word>(Instruction::Code::LOD), 15,
      static_cast<Word>(Instruction::Code::OUT),
      static_cast<Word>(Instruction::Code::LOD), 16,
      static_cast<Word>(Instruction::Code::OUT),
      static_cast<Word>(Instruction::Code::HLT), 'a', 'b', 'c', 'd'});
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "cd");
}

TEST_CASE("An emulator has an accumulator that can be manipulated") {
  std::stringstream input;
  std::stringstream output;
  WordStream program(
      std::vector<Word>{static_cast<Word>(Instruction::Code::LOD), 10,
                        static_cast<Word>(Instruction::Code::ADD), 11,
                        static_cast<Word>(Instruction::Code::OUT),
                        static_cast<Word>(Instruction::Code::CLA),
                        static_cast<Word>(Instruction::Code::ADD), 11,
                        static_cast<Word>(Instruction::Code::OUT),
                        static_cast<Word>(Instruction::Code::HLT), '0', '!'});
  Emulator emu(&program, &input, &output, Accumulator('0'));

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "Q!");
}

TEST_CASE("An emulator has a pointer that can jump") {
  struct TestCase {
    Instruction::Code branch_instruction;
    Word accumulator_value;
    bool expected_branch_success;
  };
  static constexpr TestCase tests[]{
      {Instruction::Code::BZE, 0, true},  {Instruction::Code::BZE, -1, false},
      {Instruction::Code::BZE, 2, false}, {Instruction::Code::BNE, 0, false},
      {Instruction::Code::BNE, -2, true}, {Instruction::Code::BNE, 1, false},
      {Instruction::Code::BRA, 0, true},  {Instruction::Code::BRA, -1, true},
      {Instruction::Code::BRA, 1, true}};

  for (const TestCase &test : tests) {
    std::stringstream input;
    std::stringstream output;
    WordStream program(
        std::vector<Word>{static_cast<Word>(test.branch_instruction), 6,
                          static_cast<Word>(Instruction::Code::LOD), 10,
                          static_cast<Word>(Instruction::Code::OUT),
                          static_cast<Word>(Instruction::Code::HLT),
                          static_cast<Word>(Instruction::Code::LOD), 11,
                          static_cast<Word>(Instruction::Code::OUT),
                          static_cast<Word>(Instruction::Code::HLT), '0', '1'});
    Emulator emu(&program, &input, &output,
                 Accumulator(test.accumulator_value));

    REQUIRE(emu.Run().IsOk());
    if (test.expected_branch_success) {
      REQUIRE(output.str() == "1");
    } else {
      REQUIRE(output.str() == "0");
    }
  }
}

TEST_CASE("An emulator can halt") {
  std::stringstream input;
  std::stringstream output;
  WordStream program(
      std::vector<Word>{static_cast<Word>(Instruction::Code::HLT),
                        static_cast<Word>(Instruction::Code::LOD), 5,
                        static_cast<Word>(Instruction::Code::OUT),
                        static_cast<Word>(Instruction::Code::HLT), 'a'});
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "");
}
