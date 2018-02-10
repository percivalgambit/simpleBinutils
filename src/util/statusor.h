#ifndef UTIL_STATUSOR_H_
#define UTIL_STATUSOR_H_

// Copied from https://github.com/google/lmctfy/blob/master/util/task/statusor.h

#include "util/panic.h"
#include "util/status.h"

namespace util {

template <typename T>
class[[nodiscard]] StatusOr {
 public:
  StatusOr(const Status& status);

  StatusOr(const T& value);

  ~StatusOr();

  template <typename U>
  StatusOr(const StatusOr<U>& other);

  template <typename U>
  const StatusOr& operator=(const StatusOr<U>& other);

  const Status& GetStatus() const;

  bool IsOk() const;

  const T& ValueOrDie() const;

  template <typename U>
  friend class StatusOr;

 private:
  bool isOK_;
  union {
    Status status_;
    T value_;
  };
};

template <typename T>
StatusOr<T>::StatusOr(const Status& status) : isOK_(false), status_(status) {
  if (status.IsOk()) {
    Panic("Status::OK is not a valid argument to StatusOr");
  }
}

template <typename T>
StatusOr<T>::StatusOr(const T& value) : isOK_(true), value_(value) {}

template <typename T>
StatusOr<T>::~StatusOr() {
  if (isOK_) {
    value_.~T();
  } else {
    status_.~Status();
  }
}

template <typename T>
template <typename U>
StatusOr<T>::StatusOr(const StatusOr<U>& other) {
  if (other.isOK_) {
    isOK_ = true;
    value_ = other.value_;
  } else {
    isOK_ = false;
    new (&status_) Status(other.status_);
  }
}

template <typename T>
template <typename U>
const StatusOr<T>& StatusOr<T>::operator=(const StatusOr<U>& other) {
  if (other.isOK_) {
    isOK_ = true;
    value_ = other.value_;
  } else {
    isOK_ = false;
    new (&status_) Status(other.status_);
  }
  return *this;
}

template <typename T>
const Status& StatusOr<T>::GetStatus() const {
  if (isOK_) {
    return Status::OK;
  }
  return status_;
}

template <typename T>
bool StatusOr<T>::IsOk() const {
  return isOK_;
}

template <typename T>
const T& StatusOr<T>::ValueOrDie() const {
  if (!isOK_) {
    Panic("Attempting to fetch value of non-OK StatusOr");
  }
  return value_;
}

}  // namespace util

#endif  // UTIL_STATUSOR_H_
