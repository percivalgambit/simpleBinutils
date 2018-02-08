#include "emulator/decode_instruction.h"

#include <string>

#include "common/instruction.h"
#include "emulator/memory.h"
#include "util/status.h"
#include "util/statusor.h"

using common::Instruction;
using common::Word;
using util::Status;
using util::StatusOr;

namespace emulator {

StatusOr<Instruction> DecodeInstruction(Memory *memory) {
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
      return Instruction(code);
    default:
      return Status(Status::Code::kInvalid,
                    "Opcode " + std::to_string(static_cast<int>(code)) +
                        " is not a valid instruction code");
  }
}

}  // namespace emulator
