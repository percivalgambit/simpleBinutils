#include "emulator/emulator.h"

#include <iostream>
#include <sstream>
#include <string>

#include "asserts.h"

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/accumulator.h"

using common::Instruction;
using common::Word;
using emulator::Accumulator;
using emulator::Emulator;

void TestWriteOutput();
void TestLoad();
void TestStore();
void TestClear();
void TestAdd();
void TestBranchZero();
void TestBranchNegative();
void TestBranchUnconditional();
void TestReadInput();
void TestHalt();
void TestRun();

int main() {
  TestWriteOutput();
  TestLoad();
  TestStore();
  TestClear();
  TestAdd();
  TestBranchZero();
  TestBranchNegative();
  TestBranchUnconditional();
  TestReadInput();
  TestHalt();
  TestRun();

  return 0;
}

Emulator newEmulator(const std::string &program, std::istream *input,
                     std::ostream *output, const Accumulator acc) {
  std::basic_string<Word> converted_program(program.cbegin(), program.cend());
  std::basic_stringstream<Word> program_stream(converted_program);
  return Emulator(&program_stream, input, output, acc);
}

Emulator newEmulator(const std::string &program, std::istream *input,
                     std::ostream *output) {
  return newEmulator(program, input, output, Accumulator());
}

Emulator newEmulator(const std::string &program) {
  return newEmulator(program, &std::cin, &std::cout);
}

void TestWriteOutput() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("foo", &input, &output, Accumulator('b'));

  emu.WriteOutput();
  ASSERT_EQ(output.str(), "b");

  // TODO: Test failure when halted
}

void TestLoad() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("foo", &input, &output);

  emu.Load(0);
  emu.WriteOutput();
  emu.Load(1);
  emu.WriteOutput();
  emu.Load(2);
  emu.WriteOutput();
  ASSERT_EQ(output.str(), "foo");

  // TODO: Test failure when halted
}

void TestStore() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("foobar", &input, &output);

  emu.Load(3);
  emu.Store(0);
  emu.Load(4);
  emu.Store(1);
  emu.Load(5);
  emu.Store(2);

  emu.Load(0);
  emu.WriteOutput();
  emu.Load(1);
  emu.WriteOutput();
  emu.Load(2);
  emu.WriteOutput();
  ASSERT_EQ(output.str(), "bar");

  // TODO: Test failure when halted
}

void TestClear() {
  std::istringstream input;
  std::stringstream output;
  Emulator emu = newEmulator("foo", &input, &output, Accumulator('b'));

  emu.Clear();
  emu.WriteOutput();
  ASSERT_EQ(output.get(), '\0');

  // TODO: Test failure when halted
}

void TestAdd() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("!", &input, &output, Accumulator('0'));

  emu.Add(0);
  emu.WriteOutput();
  ASSERT_EQ(output.str(), "Q");

  // TODO: Test failure when halted
}

void TestBranchZero() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("bar", &input, &output, Accumulator(0));

  emu.BranchZero(2);
  ASSERT_EQ(emu.ReadPointer(), 'r');

  emu = newEmulator("bar", &input, &output, Accumulator(-3));
  emu.BranchZero(2);
  ASSERT_EQ(emu.ReadPointer(), 'b');

  // TODO: Test failure when halted
}

void TestBranchNegative() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("bar", &input, &output, Accumulator(0));

  emu.BranchNegative(2);
  ASSERT_EQ(emu.ReadPointer(), 'b');

  emu = newEmulator("bar", &input, &output, Accumulator(-3));
  emu.BranchNegative(2);
  ASSERT_EQ(emu.ReadPointer(), 'r');

  // TODO: Test failure when halted
}

void TestBranchUnconditional() {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("bar", &input, &output, Accumulator(0));

  emu.BranchUnconditional(2);
  ASSERT_EQ(emu.ReadPointer(), 'r');

  emu = newEmulator("bar", &input, &output, Accumulator(-3));
  emu.BranchUnconditional(2);
  ASSERT_EQ(emu.ReadPointer(), 'r');

  // TODO: Test failure when halted
}

void TestReadInput() {
  std::stringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("foo", &input, &output);

  input << 'b';
  emu.ReadInput();
  emu.WriteOutput();
  ASSERT_EQ(output.str(), "b");

  // TODO: Test failure when halted
}

void TestHalt() {
  Emulator emu = newEmulator("foo");

  emu.Halt();

  assert(emu.IsHalted());

  // TODO: Test failure when halted
}

void TestRun() {
  std::istringstream input;
  std::stringstream output;
  Emulator emu = newEmulator({char(Instruction::Code::LOD),
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
                              'o'},
                             &input, &output);

  emu.Run();
  ASSERT_EQ(output.str(), "hello");
}
