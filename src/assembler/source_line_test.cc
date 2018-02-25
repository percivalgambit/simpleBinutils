#include "assembler/source_line.h"

#include <string>

#include "test_util/catch.hpp"

using assembler::SourceLine;

TEST_CASE("A SourceLine can be parsed from a line of assembly") {
  static constexpr struct {
    const char *input;
    const char *label;
    const char *mnemonic;
    const char *operand;
    const char *comment;
  } tests[]{{"Label: Mnemonic Operand ;Comment", "Label", "Mnemonic", "Operand",
             "Comment"},
            {"Mnemonic Operand ;Comment", "", "Mnemonic", "Operand", "Comment"},
            {"Mnemonic", "", "Mnemonic", "", ""},
            {"EI ;Enable interrupts", "", "EI", "", "Enable interrupts"},
            {";A comment; with ; ;semicolons", "", "", "",
             "A comment; with ; ;semicolons"}};

  for (const auto &test : tests) {
    INFO("Test case: {input: "
         << test.input << ", expected label: " << test.label
         << ", expected mnemonic: " << test.mnemonic << ", expected operand: "
         << test.operand << ", expected comment: " << test.comment << "}");
    SourceLine source_line = SourceLine::FromString(test.input).ValueOrDie();

    REQUIRE(source_line.GetLabel() == test.label);
    REQUIRE(source_line.GetMnemonic() == test.mnemonic);
    REQUIRE(source_line.GetOperand() == test.operand);
    REQUIRE(source_line.GetComment() == test.comment);
  }
}

TEST_CASE("An invalid line of assembly will result in a parse error") {
  static constexpr struct {
    const char *input;
  } tests[]{{""}, {"Label:"}, {"Too many tokens"}};

  for (const auto &test : tests) {
    INFO("Test case: {input: " << test.input << "}");
    REQUIRE_FALSE(SourceLine::FromString(test.input).IsOk());
  }
}
