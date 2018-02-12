#include <iostream>
#include <vector>

#include "common/constants.h"
#include "common/instruction.h"
#include "test_util/word_stream.h"

using common::Instruction;
using common::Word;
using test_util::WordStream;

int main() {
  std::vector<Word> helloProg{static_cast<Word>(Instruction::Code::LOD),
                              16,
                              static_cast<Word>(Instruction::Code::OUT),
                              static_cast<Word>(Instruction::Code::LOD),
                              17,
                              static_cast<Word>(Instruction::Code::OUT),
                              static_cast<Word>(Instruction::Code::LOD),
                              18,
                              static_cast<Word>(Instruction::Code::OUT),
                              static_cast<Word>(Instruction::Code::LOD),
                              19,
                              static_cast<Word>(Instruction::Code::OUT),
                              static_cast<Word>(Instruction::Code::LOD),
                              20,
                              static_cast<Word>(Instruction::Code::OUT),
                              static_cast<Word>(Instruction::Code::HLT),
                              'h',
                              'e',
                              'l',
                              'l',
                              'o'};
  WordStream stream(helloProg);
  std::cout << stream.rdbuf();
  return 0;
}
