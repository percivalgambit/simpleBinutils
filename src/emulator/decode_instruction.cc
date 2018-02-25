#include "emulator/decode_instruction.h"

#include <string>

#include "common/instruction.h"
#include "common/opcode.h"
#include "emulator/memory.h"
#include "util/status.h"
#include "util/statusor.h"

using common::Instruction;
using common::Opcode;
using common::Word;
using util::Status;
using util::StatusOr;

namespace emulator {

StatusOr<Instruction> DecodeInstruction(Memory *memory) {
  const Opcode code = Opcode(memory->ReadPointer());
  memory->AdvancePointer();
  const Word operand = memory->ReadPointer();
  switch (code) {
    case Opcode::LOD:
    case Opcode::STO:
    case Opcode::ADD:
    case Opcode::BZE:
    case Opcode::BNE:
    case Opcode::BRA:
      memory->AdvancePointer();
      return Instruction(code, operand);
    case Opcode::INP:
    case Opcode::OUT:
    case Opcode::CLA:
    case Opcode::HLT:
      return Instruction(code);
    default:
      return Status(Status::Code::kInvalid,
                    "Opcode " + std::to_string(static_cast<int>(code)) +
                        " is not a valid instruction code");
  }
}

}  // namespace emulator
