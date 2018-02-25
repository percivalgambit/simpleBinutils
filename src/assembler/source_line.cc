#include "assembler/source_line.h"

#include <deque>
#include <sstream>
#include <string>

#include "util/status.h"
#include "util/statusor.h"

using util::Status;
using util::StatusOr;

namespace assembler {

StatusOr<SourceLine> SourceLine::FromString(const std::string &source_line) {
  std::deque<std::string> comment_split = Split(source_line, ';');
  if (comment_split.empty()) {
    return ParseError(source_line);
  }
  std::deque<std::string> token_split = Split(comment_split[0], ' ');
  comment_split.pop_front();
  std::string label, mnemonic, operand;
  if (!token_split.empty()) {
    if (token_split[0].back() == ':') {
      label = token_split[0];
      label.pop_back();
      token_split.pop_front();
      if (token_split.empty()) {
        return ParseError(source_line);
      }
    }
    mnemonic = token_split[0];
    token_split.pop_front();
    if (!token_split.empty()) {
      operand = token_split[0];
      token_split.pop_front();
    }
    if (!token_split.empty()) {
      return ParseError(source_line);
    }
  }

  std::stringstream comment;
  if (!comment_split.empty()) {
    comment << comment_split[0];
    comment_split.pop_front();
    while (!comment_split.empty()) {
      comment << ';' << comment_split[0];
      comment_split.pop_front();
    }
  }
  return SourceLine(label, mnemonic, operand, comment.str());
}

std::string SourceLine::GetLabel() const { return label_; }
std::string SourceLine::GetMnemonic() const { return mnemonic_; }
std::string SourceLine::GetOperand() const { return operand_; }
std::string SourceLine::GetComment() const { return comment_; }

SourceLine::SourceLine(const std::string &label, const std::string &mnemonic,
                       const std::string &operand, const std::string &comment)
    : label_(label),
      mnemonic_(mnemonic),
      operand_(operand),
      comment_(comment) {}

std::deque<std::string> SourceLine::Split(const std::string &str,
                                          const char delim) {
  std::istringstream stream(str);
  std::deque<std::string> tokens;
  std::string token;
  while (std::getline(stream, token, delim)) {
    tokens.push_back(token);
  }
  return tokens;
}

Status SourceLine::ParseError(const std::string &source_line) {
  return Status(Status::Code::kNoParse,
                "Can't parse source line: " + source_line);
}

}  // namespace assembler
