#include "catch.hpp"

#include "util/status.h"

using util::Status;

TEST_CASE("Status objects can be OK (no error)") {
  Status ok(Status::Code::kOK);

  REQUIRE(ok == Status::OK);
  REQUIRE(ok.IsOk());
  REQUIRE(Status::OK.IsOk());
  REQUIRE(ok.StatusCode() == Status::Code::kOK);

  REQUIRE(ok == Status::OK);
  REQUIRE(ok != Status(Status::Code::kInvalid));

  REQUIRE(ok.ToString() == "OK");
}

TEST_CASE("Status objects can be an error") {
  Status error(Status::Code::kInvalid);
  REQUIRE_FALSE(error.IsOk());
  REQUIRE(error.StatusCode() == Status::Code::kInvalid);

  REQUIRE(error == Status(Status::Code::kInvalid));
  REQUIRE(error != Status::OK);
  REQUIRE(error != Status(Status::Code::kOutOfBounds));

  REQUIRE(error.ToString() == "INVALID: ");
}

TEST_CASE("Errors can have messages") {
  Status error(Status::Code::kInvalid, "foo");

  REQUIRE(error == error);
  REQUIRE(error != Status(Status::Code::kInvalid, "bar"));

  REQUIRE(Status::OK.Message() == "");
  REQUIRE(error.Message() == "foo");

  REQUIRE(error.ToString() == "INVALID: foo");
}
