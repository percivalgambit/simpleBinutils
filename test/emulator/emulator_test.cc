#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include "widen_string.h"

#include "common/constants.h"
#include "common/instruction.h"
#include "emulator/accumulator.h"
#include "emulator/emulator.h"

using common::Instruction;
using common::Word;
using emulator::Accumulator;
using emulator::Emulator;
using tests::WidenString;

Emulator newEmulator(const std::string &program, std::istream *input,
                     std::ostream *output, const Accumulator acc) {
  const std::string &converted_program = WidenString(program);
  std::stringstream program_stream(converted_program);
  return Emulator(&program_stream, input, output, acc);
}

Emulator newEmulator(const std::string &program, std::istream *input,
                     std::ostream *output) {
  return newEmulator(program, input, output, Accumulator());
}

Emulator newEmulator(const std::string &program) {
  return newEmulator(program, &std::cin, &std::cout);
}

TEST_CASE("An emulator can read and write characters") {
  std::stringstream input;
  std::stringstream output;
  Emulator emu = newEmulator("foo", &input, &output, Accumulator('b'));

  emu.WriteOutput();
  REQUIRE(output.str() == "b");
  input << 'c';
  emu.ReadInput();
  emu.WriteOutput();
  REQUIRE(output.str() == "bc");
}

TEST_CASE("An emulator can load and store values in memory") {
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
  REQUIRE(output.str() == "bar");
}

TEST_CASE("An emulator has an accumulator that can be manipulated") {
  std::stringstream input;
  std::stringstream output;
  Emulator emu = newEmulator("!", &input, &output, Accumulator('0'));

  emu.Add(0);
  emu.WriteOutput();
  REQUIRE(output.str() == "Q");

  output.str("");
  emu.Clear();
  emu.WriteOutput();
  REQUIRE(output.get() == '\0');
}

TEST_CASE("An emulator has a pointer that can jump") {
  std::istringstream input;
  std::ostringstream output;
  Emulator emu = newEmulator("bar", &input, &output, Accumulator(0));

  emu.BranchZero(2);
  REQUIRE(emu.ReadPointer() == 'r');
  emu.BranchNegative(1);
  REQUIRE(emu.ReadPointer() == 'r');
  emu.BranchUnconditional(0);
  REQUIRE(emu.ReadPointer() == 'b');

  emu = newEmulator("bar", &input, &output, Accumulator(-1));
  emu.BranchZero(2);
  REQUIRE(emu.ReadPointer() == 'b');
  emu.BranchNegative(1);
  REQUIRE(emu.ReadPointer() == 'a');
  emu.BranchUnconditional(0);
  REQUIRE(emu.ReadPointer() == 'b');
}

TEST_CASE("An emulator can halt") {
  Emulator emu = newEmulator("foo");

  emu.Halt();
  REQUIRE(emu.IsHalted());
}

TEST_CASE("An emulator can run a program") {
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
  REQUIRE(output.str() == "hello");
}

// TODO: Test failure when halted
