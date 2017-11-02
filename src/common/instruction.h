#ifndef COMMON_INSTRUCTION_H_
#define COMMON_INSTRUCTION_H_

#include <experimental/optional>

#include "common/constants.h"

namespace common {

struct Instruction {
  enum class Code : Word {
    LOD = 1,
    STO = 2,
    ADD = 3,
    BZE = 4,
    BNE = 5,
    BRA = 6,
    INP = 7,
    OUT = 8,
    CLA = 9,
    HLT = 0
  };

  Instruction(const Code code) : code(code) {}

  Instruction(const Code code, const Word operand)
      : code(code), operand(operand) {}

  Code code;
  std::experimental::optional<Word> operand;
};

}  // namespace common

#endif  // COMMON_INSTRUCTION_H_
