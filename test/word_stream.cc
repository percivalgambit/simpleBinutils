#include "word_stream.h"

#include <istream>
#include <string>
#include <vector>

#include "common/constants.h"

namespace test {

WordStream::WordStream(const std::vector<common::Word> &vec)
    : std::istream(&buffer_), buffer_(vec) {
  rdbuf(&buffer_);
}

WordStream::WordStream(const std::string &str)
    : WordStream(std::vector<common::Word>(str.cbegin(), str.cend())) {}

WordStream::WordBuffer::WordBuffer(const std::vector<common::Word> &vec) {
  data_ = vec;
  setg(reinterpret_cast<char *>(data_.data()),
       reinterpret_cast<char *>(data_.data()),
       reinterpret_cast<char *>(data_.data() + data_.size()));
}

}  // namespace test
