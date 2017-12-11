#include "util/status.h"

#include "asserts.h"

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
  ASSERT_EQ(ok_status, Status::OK);
  ASSERT_NEQ(ok_status, Status(Status::Code::kInvalid));

  Status invalid_status(Status::Code::kInvalid);
  ASSERT_EQ(invalid_status, invalid_status);
  ASSERT_NEQ(invalid_status, Status::OK);
  ASSERT_NEQ(invalid_status, Status(Status::Code::kOutOfBounds));

  Status invalid_message_status(Status::Code::kInvalid, "foo");
  ASSERT_NEQ(invalid_status, invalid_message_status);
  ASSERT_EQ(invalid_message_status, Status(Status::Code::kInvalid, "foo"));
  ASSERT_NEQ(invalid_message_status, Status(Status::Code::kInvalid, "bar"));
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
  ASSERT_EQ(ok_status.StatusCode(), Status::Code::kOK);
  ASSERT_EQ(Status::OK.StatusCode(), Status::Code::kOK);

  Status invalid_status(Status::Code::kInvalid);
  ASSERT_EQ(invalid_status.StatusCode(), Status::Code::kInvalid);
}

void TestMessage() {
  Status no_message_status;
  ASSERT_EQ(no_message_status.Message(), "");
  ASSERT_EQ(Status::OK.Message(), "");

  Status message_status = Status(Status::Code::kOutOfBounds, "foo");
  ASSERT_EQ(message_status.Message(), "foo");
}

void TestToString() {
  Status no_message_status(Status::Code::kInvalid);
  ASSERT_EQ(no_message_status.ToString(), "");

  Status ok_status;
  ASSERT_EQ(ok_status.ToString(), "OK");
  ASSERT_EQ(Status::OK.ToString(), "OK");

  Status message_status = Status(Status::Code::kOutOfBounds, "foo");
  ASSERT_EQ(message_status.ToString(), "foo");
}
