#include "emulator/emulator.h"

#include <iostream>

#include "common/constants.h"
#include "common/instruction.h"
#include "common/opcode.h"
#include "emulator/accumulator.h"
#include "emulator/decode_instruction.h"
#include "util/panic.h"
#include "util/status.h"
#include "util/statusor.h"

using common::Instruction;
using common::Opcode;
using common::Word;
using emulator::Accumulator;
using util::Panic;
using util::Status;
using util::StatusOr;

namespace emulator {

Emulator::Emulator(std::istream* program)
    : Emulator(program, &std::cin, &std::cout, Accumulator()) {}

Emulator::Emulator(std::istream* program, std::istream* input,
                   std::ostream* output, const Accumulator acc)
    : acc_(acc),
      mem_(program),
      input_(input),
      output_(output),
      is_halted_(false) {}

#define EXECUTE_ONE_OPERAND(code_name, func) \
  case Opcode::code_name:                    \
    status = func(*instruction.operand);     \
    if (!status.IsOk()) {                    \
      return status;                         \
    }                                        \
    break;

#define EXECUTE_ZERO_OPERANDS(code_name, func) \
  case Opcode::code_name:                      \
    status = func();                           \
    if (!status.IsOk()) {                      \
      return status;                           \
    }                                          \
    break

Status Emulator::Run() {
  while (!IsHalted()) {
    const StatusOr<Instruction>& instruction_or = DecodeInstruction(&mem_);
    if (!instruction_or.IsOk()) {
      return instruction_or.GetStatus();
    }
    const Instruction& instruction = instruction_or.ValueOrDie();
    Status status;
    switch (instruction.code) {
      EXECUTE_ONE_OPERAND(LOD, Load);
      EXECUTE_ONE_OPERAND(STO, Store);
      EXECUTE_ONE_OPERAND(ADD, Add);
      EXECUTE_ONE_OPERAND(BZE, BranchZero);
      EXECUTE_ONE_OPERAND(BNE, BranchNegative);
      EXECUTE_ONE_OPERAND(BRA, BranchUnconditional);
      EXECUTE_ZERO_OPERANDS(INP, ReadInput);
      EXECUTE_ZERO_OPERANDS(OUT, WriteOutput);
      EXECUTE_ZERO_OPERANDS(CLA, Clear);
      EXECUTE_ZERO_OPERANDS(HLT, Halt);
      default:
        return Status(Status::Code::kInvalid);
    }
  }
  return Status::OK;
}

Status Emulator::Load(const size_t operand) {
  StatusOr<Word> loaded_value = mem_.Load(operand);
  if (!loaded_value.IsOk()) {
    return loaded_value.GetStatus();
  }
  acc_.Set(loaded_value.ValueOrDie());
  return Status::OK;
}

Status Emulator::Store(const size_t operand) {
  return mem_.Store(operand, acc_.Get());
}

Status Emulator::Clear() {
  acc_.Reset();
  return Status::OK;
}

Status Emulator::Add(const size_t operand) {
  StatusOr<Word> loaded_value = mem_.Load(operand);
  if (!loaded_value.IsOk()) {
    return loaded_value.GetStatus();
  }
  acc_.Add(loaded_value.ValueOrDie());
  return Status::OK;
}

Status Emulator::BranchZero(const size_t operand) {
  if (acc_.Get() == 0) {
    return mem_.Jump(operand);
  }
  return Status::OK;
}

Status Emulator::BranchNegative(const size_t operand) {
  if (acc_.Get() < 0) {
    return mem_.Jump(operand);
  }
  return Status::OK;
}

Status Emulator::BranchUnconditional(const size_t operand) {
  return mem_.Jump(operand);
}

Status Emulator::ReadInput() {
  char input_word;
  *input_ >> input_word;
  acc_.Set(input_word);
  return Status::OK;
}

Status Emulator::WriteOutput() {
  Word output_word = acc_.Get();
  *output_ << char(output_word);
  return Status::OK;
}

Status Emulator::Halt() {
  is_halted_ = true;
  return Status::OK;
}

bool Emulator::IsHalted() const { return is_halted_; }

Word Emulator::ReadPointer() const { return mem_.ReadPointer(); }

}  // namespace emulator
