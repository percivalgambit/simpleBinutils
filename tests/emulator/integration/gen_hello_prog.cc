#include <iostream>
#include <string>

#include "widen_string.h"

#include "common/instruction.h"

using common::Instruction;

static constexpr char kHelloProg[] = {char(Instruction::Code::LOD),
                                      16,
                                      char(Instruction::Code::OUT),
                                      char(Instruction::Code::LOD),
                                      17,
                                      char(Instruction::Code::OUT),
                                      char(Instruction::Code::LOD),
                                      18,
                                      char(Instruction::Code::OUT),
                                      char(Instruction::Code::LOD),
                                      19,
                                      char(Instruction::Code::OUT),
                                      char(Instruction::Code::LOD),
                                      20,
                                      char(Instruction::Code::OUT),
                                      char(Instruction::Code::HLT),
                                      'h',
                                      'e',
                                      'l',
                                      'l',
                                      'o'};

int main() {
  std::string char_prog(kHelloProg, sizeof(kHelloProg));
  std::string converted_prog = tests::WidenString(char_prog);
  std::cout << converted_prog;
  return 0;
}
