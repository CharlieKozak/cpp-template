#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include "calculator/calculate.h"

using calculator::calculate;

TEST_CASE("addition works") {
  std::istringstream in("eq\n2\n+\n3\n");
  std::ostringstream out;
  calculate(in, out);
  auto s = out.str();
  REQUIRE(s.find("5") != std::string::npos);
}

TEST_CASE("multiplication works") {
  std::istringstream in("eq\n4\n*\n2\n");
  std::ostringstream out;
  calculate(in, out);
  auto s = out.str();
  REQUIRE(s.find("8") != std::string::npos);
}

TEST_CASE("division by zero error") {
  std::istringstream in("eq\n1\n/\n0\n");
  std::ostringstream out;
  calculate(in, out);
  auto s = out.str();
  REQUIRE(s.find("Error: Division by zero!") != std::string::npos);
}
