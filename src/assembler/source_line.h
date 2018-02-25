#ifndef ASSEMBLER_SOURCE_LINE_H_
#define ASSEMBLER_SOURCE_LINE_H_

#include <deque>
#include <string>

#include "util/statusor.h"

namespace assembler {

class SourceLine {
 public:
  static util::StatusOr<SourceLine> FromString(const std::string &source_line);

  std::string GetLabel() const;
  std::string GetMnemonic() const;
  std::string GetOperand() const;
  std::string GetComment() const;

 private:
  SourceLine(const std::string &label, const std::string &mnemonic,
             const std::string &operand, const std::string &comment);

  static std::deque<std::string> Split(const std::string &str,
                                       const char delim);

  static util::Status ParseError(const std::string &source_line);

  std::string label_;
  std::string mnemonic_;
  std::string operand_;
  std::string comment_;
};

}  // namespace assembler

#endif  // ASSEMBLER_SOURCE_LINE_H_
