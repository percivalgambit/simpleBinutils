#include <iostream>
#include <vector>

#include "common/constants.h"
#include "common/opcode.h"
#include "test_util/word_stream.h"

using common::Opcode;
using common::Word;
using test_util::WordStream;

int main() {
  std::vector<Word> helloProg{static_cast<Word>(Opcode::LOD),
                              16,
                              static_cast<Word>(Opcode::OUT),
                              static_cast<Word>(Opcode::LOD),
                              17,
                              static_cast<Word>(Opcode::OUT),
                              static_cast<Word>(Opcode::LOD),
                              18,
                              static_cast<Word>(Opcode::OUT),
                              static_cast<Word>(Opcode::LOD),
                              19,
                              static_cast<Word>(Opcode::OUT),
                              static_cast<Word>(Opcode::LOD),
                              20,
                              static_cast<Word>(Opcode::OUT),
                              static_cast<Word>(Opcode::HLT),
                              'h',
                              'e',
                              'l',
                              'l',
                              'o'};
  WordStream stream(helloProg);
  std::cout << stream.rdbuf();
  return 0;
}
