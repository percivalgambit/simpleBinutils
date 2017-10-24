#include "emulator.h"

#include "constants.h"
#include "status.h"

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
