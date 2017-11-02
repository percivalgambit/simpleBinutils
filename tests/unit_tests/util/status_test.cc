#include "util/status.h"

#include <cassert>

using util::Status;

void TestEquality();
void TestIsOk();
void TestStatusCode();
void TestMessage();
void TestToString();

int main() {
  TestEquality();
  TestIsOk();
  TestStatusCode();
  TestMessage();
  TestToString();

  return 0;
}

void TestEquality() {
  Status ok_status(Status::Code::kOK);
  assert(ok_status == Status::OK);
  assert(ok_status != Status(Status::Code::kInvalid));

  Status halted_status(Status::Code::kIsHalted);
  assert(halted_status == halted_status);
  assert(halted_status != Status::OK);
  assert(halted_status != Status(Status::Code::kOutOfBounds));

  Status halted_message_status(Status::Code::kIsHalted, "foo");
  assert(halted_status != halted_message_status);
  assert(halted_message_status == Status(Status::Code::kIsHalted, "foo"));
  assert(halted_message_status != Status(Status::Code::kIsHalted, "bar"));
}

void TestIsOk() {
  Status ok_status(Status::Code::kOK);
  assert(ok_status.IsOk());
  assert(Status::OK.IsOk());

  Status not_ok_status(Status::Code::kOutOfBounds);
  assert(!not_ok_status.IsOk());
}

void TestStatusCode() {
  Status ok_status(Status::Code::kOK);
  assert(ok_status.StatusCode() == Status::Code::kOK);
  assert(Status::OK.StatusCode() == Status::Code::kOK);

  Status halted_status(Status::Code::kIsHalted);
  assert(halted_status.StatusCode() == Status::Code::kIsHalted);
}

void TestMessage() {
  Status no_message_status;
  assert(no_message_status.Message() == "");
  assert(Status::OK.Message() == "");

  Status message_status = Status(Status::Code::kOutOfBounds, "foo");
  assert(message_status.Message() == "foo");
}

void TestToString() {
  Status no_message_status(Status::Code::kInvalid);
  assert(no_message_status.ToString() == "");

  Status ok_status;
  assert(ok_status.ToString() == "OK");
  assert(Status::OK.ToString() == "OK");

  Status message_status = Status(Status::Code::kOutOfBounds, "foo");
  assert(message_status.ToString() == "foo");
}
