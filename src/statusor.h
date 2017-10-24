#ifndef STATUSOR_H_
#define STATUSOR_H_

#include <cassert>

#include "status.h"

template <class T>
class StatusOr {
 public:
  StatusOr(const Status& status);

  StatusOr(const T& value);

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
  Status status_;
  T value_;
};

template <typename T>
StatusOr<T>::StatusOr(const Status& status) : status_(status) {
  // TODO: Add error message if this fails
  assert(!status_.IsOk());
}

template <typename T>
StatusOr<T>::StatusOr(const T& value) : value_(value) {}

template <typename T>
template <typename U>
StatusOr<T>::StatusOr(const StatusOr<U>& other)
    : status_(other.status_), value_(other.value_) {}

template <typename T>
template <typename U>
const StatusOr<T>& StatusOr<T>::operator=(const StatusOr<U>& other) {
  status_ = other.status_;
  if (status_.IsOk()) {
    value_ = other.value_;
  }
  return *this;
}

template <typename T>
const Status& StatusOr<T>::GetStatus() const {
  return status_;
}

template <typename T>
bool StatusOr<T>::IsOk() const {
  return status_.IsOk();
}

template <typename T>
const T& StatusOr<T>::ValueOrDie() const {
  // TODO: Add error message if this fails
  assert(IsOk());
  return value_;
}

#endif  // STATUSOR_H_
