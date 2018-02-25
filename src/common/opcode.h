#ifndef COMMON_OPCODE_H_
#define COMMON_OPCODE_H_

#include <string>

#include "common/constants.h"

namespace common {

enum class Opcode : Word {
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

enum class OpcodeType {

};

struct OpcodeTableEntry {
  Opcode opcode;
  const char *mnemonic;
  // OpcodeType type;
  // size_t length;
};

static constexpr OpcodeTableEntry kOpcodeTable[] = {
    {Opcode::LOD, "LOD"}, {Opcode::STO, "STO"}, {Opcode::ADD, "ADD"},
    {Opcode::BZE, "BZE"}, {Opcode::BNE, "BNE"}, {Opcode::BRA, "BRA"},
    {Opcode::INP, "INP"}, {Opcode::OUT, "OUT"}, {Opcode::CLA, "CLA"},
    {Opcode::HLT, "HLT"}};

}  // namespace common

#endif  // COMMON_OPCODE_H_
