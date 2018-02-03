#include "util/statusor.h"

#include "asserts.h"

#include "util/status.h"

using util::Status;
using util::StatusOr;

void TestGetStatus();
void TestIsOk();
void TestValueOrDie();

int main() {
  TestGetStatus();
  TestIsOk();
  TestValueOrDie();

  return 0;
}

void TestGetStatus() {
  StatusOr<int> statusor_value(3);
  ASSERT_EQ(statusor_value.GetStatus(), Status::OK);

  Status status(Status::Code::kInvalid);
  StatusOr<int> statusor_status(status);
  ASSERT_EQ(statusor_status.GetStatus(), status);

  StatusOr<int> statusor_original(4);
  StatusOr<double> statusor_converted(statusor_original);
  ASSERT_EQ(statusor_converted.GetStatus(), Status::OK);
}

void TestIsOk() {
  StatusOr<int> statusor_value(3);
  assert(statusor_value.IsOk());

  Status status(Status::Code::kInvalid);
  StatusOr<int> statusor_status(status);
  assert(!statusor_status.IsOk());

  StatusOr<int> statusor_original(4);
  StatusOr<double> statusor_converted(statusor_original);
  assert(statusor_converted.IsOk());
}

void TestValueOrDie() {
  StatusOr<int> statusor_value(3);
  ASSERT_EQ(statusor_value.ValueOrDie(), 3);

  // TODO: Add a test for failure
  Status status(Status::Code::kInvalid);
  StatusOr<int> statusor_status(status);

  StatusOr<int> statusor_original(4);
  StatusOr<double> statusor_converted(statusor_original);
  ASSERT_EQ(statusor_converted.ValueOrDie(), 4.0);
}
