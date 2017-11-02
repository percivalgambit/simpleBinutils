#ifndef EMULATOR_DECODE_INSTRUCTION_
#define EMULATOR_DECODE_INSTRUCTION_

#include "common/instruction.h"
#include "emulator/memory.h"

namespace emulator {

common::Instruction DecodeInstruction(Memory *memory);

}  // namespace emulator

#endif  // DECODE_INSTRUCTION_
