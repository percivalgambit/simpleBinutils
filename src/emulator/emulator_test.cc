#include "emulator/emulator.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "common/constants.h"
#include "common/opcode.h"
#include "emulator/accumulator.h"
#include "test_util/catch.hpp"
#include "test_util/word_stream.h"
#include "util/find.h"

using common::Opcode;
using common::OpcodeTableEntry;
using common::Word;
using common::kOpcodeTable;
using emulator::Accumulator;
using emulator::Emulator;
using test_util::WordStream;
using util::FindOrDie;

TEST_CASE("An emulator can read and write characters") {
  std::stringstream input;
  std::stringstream output;
  WordStream program(std::vector<Word>{
      static_cast<Word>(Opcode::OUT), static_cast<Word>(Opcode::INP),
      static_cast<Word>(Opcode::OUT), static_cast<Word>(Opcode::HLT)});
  Emulator emu(&program, &input, &output, Accumulator('b'));

  input << 'c';
  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "bc");
}

TEST_CASE("An emulator can load and store values in memory") {
  std::istringstream input;
  std::ostringstream output;
  WordStream program(std::vector<Word>{
      static_cast<Word>(Opcode::LOD), 17, static_cast<Word>(Opcode::STO), 15,
      static_cast<Word>(Opcode::LOD), 18, static_cast<Word>(Opcode::STO), 16,
      static_cast<Word>(Opcode::LOD), 15, static_cast<Word>(Opcode::OUT),
      static_cast<Word>(Opcode::LOD), 16, static_cast<Word>(Opcode::OUT),
      static_cast<Word>(Opcode::HLT), 'a', 'b', 'c', 'd'});
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "cd");
}

TEST_CASE("An emulator has an accumulator that can be manipulated") {
  std::stringstream input;
  std::stringstream output;
  WordStream program(std::vector<Word>{
      static_cast<Word>(Opcode::LOD), 10, static_cast<Word>(Opcode::ADD), 11,
      static_cast<Word>(Opcode::OUT), static_cast<Word>(Opcode::CLA),
      static_cast<Word>(Opcode::ADD), 11, static_cast<Word>(Opcode::OUT),
      static_cast<Word>(Opcode::HLT), '0', '!'});
  Emulator emu(&program, &input, &output, Accumulator('0'));

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "Q!");
}

TEST_CASE("An emulator has a pointer that can jump") {
  static constexpr struct {
    Opcode branch_instruction;
    Word accumulator_value;
    bool expected_branch_success;
  } tests[]{{Opcode::BZE, 0, true},  {Opcode::BZE, -1, false},
            {Opcode::BZE, 2, false}, {Opcode::BNE, 0, false},
            {Opcode::BNE, -2, true}, {Opcode::BNE, 1, false},
            {Opcode::BRA, 0, true},  {Opcode::BRA, -1, true},
            {Opcode::BRA, 1, true}};

  for (const auto &test : tests) {
    INFO("Test case: {instruction: "
         << (FindOrDie(kOpcodeTable, &OpcodeTableEntry::opcode,
                       test.branch_instruction)
                 .mnemonic)
         << ", accumulator: " << test.accumulator_value
         << ", expected: " << test.expected_branch_success << "}");
    std::stringstream input;
    std::stringstream output;
    WordStream program(std::vector<Word>{
        static_cast<Word>(test.branch_instruction), 6,
        static_cast<Word>(Opcode::LOD), 10, static_cast<Word>(Opcode::OUT),
        static_cast<Word>(Opcode::HLT), static_cast<Word>(Opcode::LOD), 11,
        static_cast<Word>(Opcode::OUT), static_cast<Word>(Opcode::HLT), '0',
        '1'});
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
  WordStream program(std::vector<Word>{
      static_cast<Word>(Opcode::HLT), static_cast<Word>(Opcode::LOD), 5,
      static_cast<Word>(Opcode::OUT), static_cast<Word>(Opcode::HLT), 'a'});
  Emulator emu(&program, &input, &output, Accumulator());

  REQUIRE(emu.Run().IsOk());
  REQUIRE(output.str() == "");
}
