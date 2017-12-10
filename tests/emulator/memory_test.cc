#include "emulator/memory.h"

#include <sstream>
#include <string>

#include "asserts.h"

#include "common/constants.h"

using common::kMemorySize;
using common::Word;
using emulator::Memory;

void TestLoad();
void TestStore();
void TestInstructionPointer();

int main() {
  TestLoad();
  TestStore();
  TestInstructionPointer();

  return 0;
}

Memory newMemory(const std::string &program) {
  std::basic_string<Word> converted_program(program.cbegin(), program.cend());
  std::basic_stringstream<Word> program_stream(converted_program);
  return Memory(&program_stream);
}

void TestLoad() {
  Memory mem = newMemory("foo");

  ASSERT_VALUE_EQ(mem.Load(0), 'f');
  ASSERT_VALUE_EQ(mem.Load(1), 'o');
  ASSERT_VALUE_EQ(mem.Load(2), 'o');
  ASSERT_NOT_OK(mem.Load(kMemorySize));
}

void TestStore() {
  Memory mem = newMemory("b");

  ASSERT_OK(mem.Store(0, 'c'));
  ASSERT_OK(mem.Store(0, 'f'));
  ASSERT_OK(mem.Store(1, 'o'));
  ASSERT_OK(mem.Store(2, 'o'));
  ASSERT_NOT_OK(mem.Store(kMemorySize, 'c'));

  ASSERT_VALUE_EQ(mem.Load(0), 'f');
  ASSERT_VALUE_EQ(mem.Load(1), 'o');
  ASSERT_VALUE_EQ(mem.Load(2), 'o');
}

void TestInstructionPointer() {
  Memory mem = newMemory("foo");

  ASSERT_EQ(mem.ReadPointer(), 'f');
  mem.AdvancePointer();
  ASSERT_EQ(mem.ReadPointer(), 'o');
  mem.AdvancePointer();
  ASSERT_EQ(mem.ReadPointer(), 'o');
  mem.AdvancePointer();

  ASSERT_OK(mem.Jump(0));
  ASSERT_EQ(mem.ReadPointer(), 'f');
  mem.AdvancePointer();
  ASSERT_EQ(mem.ReadPointer(), 'o');
  mem.AdvancePointer();
  ASSERT_EQ(mem.ReadPointer(), 'o');
  mem.AdvancePointer();

  ASSERT_NOT_OK(mem.Jump(kMemorySize));
}
