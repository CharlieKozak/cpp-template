// Fibonacci library tests
#include <catch2/catch_test_macros.hpp>
#include <fibonacci/fibonacci.h>

TEST_CASE("nth small values") {
  REQUIRE(fibonacci::nth(0) == 0);
  REQUIRE(fibonacci::nth(1) == 1);
  REQUIRE(fibonacci::nth(2) == 1);
  REQUIRE(fibonacci::nth(3) == 2);
  REQUIRE(fibonacci::nth(4) == 3);
  REQUIRE(fibonacci::nth(5) == 5);
  REQUIRE(fibonacci::nth(10) == 55);
}

TEST_CASE("generate first N numbers") {
  auto seq0 = fibonacci::generate(0);
  REQUIRE(seq0.size() == 0);

  auto seq1 = fibonacci::generate(1);
  REQUIRE(seq1.size() == 1);
  REQUIRE(seq1[0] == 0);

  auto seq6 = fibonacci::generate(6);
  REQUIRE(seq6.size() == 6);
  REQUIRE(seq6[0] == 0);
  REQUIRE(seq6[1] == 1);
  REQUIRE(seq6[2] == 1);
  REQUIRE(seq6[3] == 2);
  REQUIRE(seq6[4] == 3);
  REQUIRE(seq6[5] == 5);
}
