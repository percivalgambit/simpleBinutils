#ifndef COMMON_INSTRUCTION_H_
#define COMMON_INSTRUCTION_H_

#include <experimental/optional>
#include <ostream>
#include <string>

#include "common/constants.h"
#include "common/opcode.h"
#include "util/find.h"

namespace common {

struct Instruction {
  explicit Instruction(const Opcode code) : code(code) {}

  Instruction(const Opcode code, const Word operand)
      : code(code), operand(operand) {}

  bool operator==(const Instruction& other) const {
    return (this->code == other.code) && (this->operand == other.operand);
  }

  std::string ToString() const {
    std::string str =
        util::FindOrDie(kOpcodeTable, &OpcodeTableEntry::opcode, code).mnemonic;
    if (operand) {
      str += ": " + std::to_string(operand.value());
    }
    return str;
  }

  Opcode code;
  std::experimental::optional<Word> operand;
};

}  // namespace common

#endif  // COMMON_INSTRUCTION_H_
