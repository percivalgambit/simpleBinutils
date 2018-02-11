#ifndef WORD_STREAM_H_
#define WORD_STREAM_H_

#include <istream>
#include <string>
#include <vector>

#include "common/constants.h"

namespace test {

class WordStream : public std::istream {
 public:
  explicit WordStream(const std::vector<common::Word> &vec);

  explicit WordStream(const std::string &str);

 private:
  class WordBuffer : public std::basic_streambuf<char> {
   public:
    WordBuffer(const std::vector<common::Word> &vec);

   private:
    std::vector<common::Word> data_;
  };

  WordBuffer buffer_;
};

}  // namespace test

#endif  // WORD_STREAM_H_
