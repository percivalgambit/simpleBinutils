#ifndef EMULATOR_DECODE_INSTRUCTION_H_
#define EMULATOR_DECODE_INSTRUCTION_H_

#include "common/instruction.h"
#include "emulator/memory.h"
#include "util/statusor.h"

namespace emulator {

util::StatusOr<common::Instruction> DecodeInstruction(Memory *memory);

}  // namespace emulator

#endif  // EMULATOR_DECODE_INSTRUCTION_H_
