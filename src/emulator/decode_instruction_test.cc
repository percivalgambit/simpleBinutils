#include "emulator/decode_instruction.h"

#include <sstream>
#include <string>
#include <vector>

#include "common/constants.h"
#include "common/instruction.h"
#include "common/opcode.h"
#include "test_util/catch.hpp"
#include "test_util/word_stream.h"

using common::Instruction;
using common::Opcode;
using common::Word;
using emulator::DecodeInstruction;
using emulator::Memory;
using test_util::WordStream;

TEST_CASE("Instructions can be decoded") {
  WordStream program(std::vector<Word>{
      static_cast<Word>(Opcode::LOD), 20, static_cast<Word>(Opcode::STO), 21,
      static_cast<Word>(Opcode::ADD), 22, static_cast<Word>(Opcode::BZE), 23,
      static_cast<Word>(Opcode::BNE), 24, static_cast<Word>(Opcode::BRA), 25,
      static_cast<Word>(Opcode::INP), static_cast<Word>(Opcode::OUT),
      static_cast<Word>(Opcode::CLA), static_cast<Word>(Opcode::HLT),
      static_cast<Word>(-1)});
  Memory mem(&program);

  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::LOD, 20));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::STO, 21));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::ADD, 22));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::BZE, 23));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::BNE, 24));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::BRA, 25));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::INP));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::OUT));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::CLA));
  REQUIRE(DecodeInstruction(&mem).ValueOrDie() == Instruction(Opcode::HLT));

  REQUIRE_FALSE(DecodeInstruction(&mem).IsOk());
}
