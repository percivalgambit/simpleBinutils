#include "emulator.h"

#include "constants.h"
#include "decode_instruction.h"
#include "instruction.h"
#include "status.h"
#include "statusor.h"

Emulator::Emulator(Accumulator acc, Memory mem, std::istream* input,
                   std::ostream* output)
    : acc_(acc),
      mem_(mem),
      input_(input->rdbuf()),
      output_(output->rdbuf()),
      is_halted_(false) {}

Status Emulator::Run() {
  while (!IsHalted()) {
    const Instruction& instruction = DecodeInstruction(&mem_);
    Status status;
    switch (instruction.code) {
      case Instruction::Code::LOD:
        status = Load(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::STO:
        status = Store(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::ADD:
        status = Add(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::BZE:
        status = BranchZero(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::BNE:
        status = BranchNegative(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::BRA:
        status = BranchUnconditional(*instruction.operand);
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::INP:
        status = ReadInput();
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::OUT:
        status = WriteOutput();
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::CLA:
        status = Clear();
        if (!status.IsOk()) {
          return status;
        }
        break;
      case Instruction::Code::HLT:
        status = Halt();
        if (!status.IsOk()) {
          return status;
        }
        break;
      default:
        return Status(Status::Code::kInvalid);
    }
  }
  return Status::OK;
}

Status Emulator::Load(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  StatusOr<Word> loaded_value = mem_.Load(operand);
  if (!loaded_value.IsOk()) {
    return loaded_value.GetStatus();
  }
  acc_.Set(loaded_value.ValueOrDie());
  return Status::OK;
}

Status Emulator::Store(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  return mem_.Store(operand, acc_.Get());
}

Status Emulator::Clear() {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  acc_.Reset();
  return Status::OK;
}

Status Emulator::Add(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  StatusOr<Word> loaded_value = mem_.Load(operand);
  if (!loaded_value.IsOk()) {
    return loaded_value.GetStatus();
  }
  acc_.Add(loaded_value.ValueOrDie());
  return Status::OK;
}

Status Emulator::BranchZero(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  if (acc_.Get() == 0) {
    return mem_.Jump(operand);
  }
  return Status::OK;
}

Status Emulator::BranchNegative(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  if (acc_.Get() < 0) {
    return mem_.Jump(operand);
  }
  return Status::OK;
}

Status Emulator::BranchUnconditional(const size_t operand) {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  return mem_.Jump(operand);
}

Status Emulator::ReadInput() {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  Word input_word;
  input_ >> input_word;
  acc_.Set(input_word);
  return Status::OK;
}

Status Emulator::WriteOutput() {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  Word output_word = acc_.Get();
  output_ << output_word;
  return Status::OK;
}

Status Emulator::Halt() {
  if (IsHalted()) {
    return Status(Status::Code::kIsHalted);
  }
  is_halted_ = true;
  return Status::OK;
}

bool Emulator::IsHalted() const { return is_halted_; }
