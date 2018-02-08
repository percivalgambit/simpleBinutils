#ifndef WORD_STREAM_H_
#define WORD_STREAM_H_

#include <algorithm>
#include <initializer_list>
#include <istream>
#include <iterator>
#include <vector>

#include "common/constants.h"

namespace test {

class WordStream : public std::istream {
 public:
  template <typename T>
  WordStream(const T &container) : std::istream(&buffer_), buffer_(container) {
    rdbuf(&buffer_);
  }

 private:
  class WordBuffer : public std::basic_streambuf<char> {
   public:
    template <typename T>
    WordBuffer(const T &container) {
      data_.reserve(std::size(container));
      std::copy(std::begin(container), std::end(container), std::begin(data_));
      setg(reinterpret_cast<char *>(data_.data()),
           reinterpret_cast<char *>(data_.data()),
           reinterpret_cast<char *>(data_.data() + std::size(container)));
    }

   private:
    std::vector<common::Word> data_;
  };

  WordBuffer buffer_;
};

}  // namespace test

#endif  // WORD_STREAM_H_
