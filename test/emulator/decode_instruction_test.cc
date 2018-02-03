#include "emulator/decode_instruction.h"

#include <sstream>
#include <string>

#include "asserts.h"
#include "widen_string.h"

#include "common/constants.h"
#include "common/instruction.h"

using common::Instruction;
using common::Word;
using emulator::DecodeInstruction;
using emulator::Memory;
using tests::WidenString;

void TestDecodeInstruction();

int main() {
  TestDecodeInstruction();

  return 0;
}

// TODO: deduplicate from this and memory_test
Memory newMemory(const std::string &program) {
  const std::string &converted_program = WidenString(program);
  std::stringstream program_stream(converted_program);
  return Memory(&program_stream);
}

void TestDecodeInstruction() {
  Memory mem = newMemory(
      {char(Instruction::Code::LOD), 20, char(Instruction::Code::STO), 21,
       char(Instruction::Code::ADD), 22, char(Instruction::Code::BZE), 23,
       char(Instruction::Code::BNE), 24, char(Instruction::Code::BRA), 25,
       char(Instruction::Code::INP), char(Instruction::Code::OUT),
       char(Instruction::Code::CLA), char(Instruction::Code::HLT)});

  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::LOD, 20));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::STO, 21));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::ADD, 22));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::BZE, 23));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::BNE, 24));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::BRA, 25));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::INP));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::OUT));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::CLA));
  ASSERT_EQ(DecodeInstruction(&mem), Instruction(Instruction::Code::HLT));
}
