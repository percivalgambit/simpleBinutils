#include <iostream>

#include "word_stream.h"

#include "common/constants.h"
#include "common/instruction.h"

using common::Instruction;
using common::Word;
using test::WordStream;

static constexpr Word kHelloProg[] = {Word(Instruction::Code::LOD),
                                      16,
                                      Word(Instruction::Code::OUT),
                                      Word(Instruction::Code::LOD),
                                      17,
                                      Word(Instruction::Code::OUT),
                                      Word(Instruction::Code::LOD),
                                      18,
                                      Word(Instruction::Code::OUT),
                                      Word(Instruction::Code::LOD),
                                      19,
                                      Word(Instruction::Code::OUT),
                                      Word(Instruction::Code::LOD),
                                      20,
                                      Word(Instruction::Code::OUT),
                                      Word(Instruction::Code::HLT),
                                      'h',
                                      'e',
                                      'l',
                                      'l',
                                      'o'};

int main() {
  WordStream stream(kHelloProg);
  std::cout << stream.rdbuf();
  return 0;
}
