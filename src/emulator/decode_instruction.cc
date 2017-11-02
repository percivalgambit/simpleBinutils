#include "emulator/decode_instruction.h"

#include "common/instruction.h"
#include "emulator/memory.h"

using common::Instruction;
using common::Word;

namespace emulator {

Instruction DecodeInstruction(Memory *memory) {
  const Instruction::Code code = Instruction::Code(memory->ReadPointer());
  memory->AdvancePointer();
  const Word operand = memory->ReadPointer();
  switch (code) {
    case Instruction::Code::LOD:
    case Instruction::Code::STO:
    case Instruction::Code::ADD:
    case Instruction::Code::BZE:
    case Instruction::Code::BNE:
    case Instruction::Code::BRA:
      memory->AdvancePointer();
      return Instruction(code, operand);
    case Instruction::Code::INP:
    case Instruction::Code::OUT:
    case Instruction::Code::CLA:
    case Instruction::Code::HLT:
    default:
      return Instruction(code);
  }
}

}  // namespace emulator
