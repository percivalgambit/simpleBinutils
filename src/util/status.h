#ifndef UTIL_STATUS_H_
#define UTIL_STATUS_H_

// Copied from https://github.com/google/lmctfy/blob/master/util/task/status.h

#include <ostream>
#include <string>

namespace util {

class[[nodiscard]] Status {
 public:
  enum class Code {
    kOK = 0,
    kOutOfBounds,
    kInvalid,
  };

  static constexpr const char* CodeStrings[]{
      "OK",
      "OUT_OF_BOUNDS",
      "INVALID",
  };

  static const Status& OK;

  Status();
  explicit Status(const Status::Code code);
  Status(const Status::Code code, const std::string& message);

  bool operator==(const Status& other) const;
  bool operator!=(const Status& other) const;

  bool IsOk() const;
  Status::Code StatusCode() const;
  const std::string& Message() const;

  std::string ToString() const;

 private:
  Status::Code code_;
  std::string message_;
};

std::ostream& operator<<(std::ostream& os, const Status::Code code);
std::ostream& operator<<(std::ostream& os, const Status& status);

}  // namespace util

#endif  // UTIL_STATUS_H_
