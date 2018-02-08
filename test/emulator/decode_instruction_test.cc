#include "catch.hpp"

#include <sstream>
#include <string>
#include <vector>

#include "word_stream.h"

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/decode_instruction.h"

using common::Instruction;
using common::Word;
using emulator::DecodeInstruction;
using emulator::Memory;
using test::WordStream;

TEST_CASE("Instructions can be decoded") {
  WordStream program(std::vector<Word>(
      {Word(Instruction::Code::LOD), 20, Word(Instruction::Code::STO), 21,
       Word(Instruction::Code::ADD), 22, Word(Instruction::Code::BZE), 23,
       Word(Instruction::Code::BNE), 24, Word(Instruction::Code::BRA), 25,
       Word(Instruction::Code::INP), Word(Instruction::Code::OUT),
       Word(Instruction::Code::CLA), Word(Instruction::Code::HLT), Word(-1)}));
  Memory mem(&program);

  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::LOD, 20));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::STO, 21));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::ADD, 22));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::BZE, 23));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::BNE, 24));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::BRA, 25));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::INP));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::OUT));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::CLA));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() ==
          Instruction(Instruction::Code::HLT));

  REQUIRE_FALSE(DecodeInstruction(&mem).IsOk());
}
