#include "catch.hpp"

#include <sstream>
#include <string>

#include "widen_string.h"

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/decode_instruction.h"

using common::Instruction;
using common::Word;
using emulator::DecodeInstruction;
using emulator::Memory;
using tests::WidenString;

// TODO: deduplicate from this and memory_test
Memory newMemory(const std::string &program) {
  const std::string &converted_program = WidenString(program);
  std::stringstream program_stream(converted_program);
  return Memory(&program_stream);
}

TEST_CASE("Instructions can be decoded") {
  Memory mem = newMemory(
      {char(Instruction::Code::LOD), 20, char(Instruction::Code::STO), 21,
       char(Instruction::Code::ADD), 22, char(Instruction::Code::BZE), 23,
       char(Instruction::Code::BNE), 24, char(Instruction::Code::BRA), 25,
       char(Instruction::Code::INP), char(Instruction::Code::OUT),
       char(Instruction::Code::CLA), char(Instruction::Code::HLT)});

  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::LOD, 20));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::STO, 21));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::ADD, 22));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::BZE, 23));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::BNE, 24));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::BRA, 25));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::INP));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::OUT));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::CLA));
  REQUIRE(DecodeInstruction(&mem) == Instruction(Instruction::Code::HLT));
}
