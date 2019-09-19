#include <catch2/catch.hpp>
#include "math/Point.h"

TEST_CASE("Point behavior", "[point]")
{
  Point3f p {4.0f, 1.0f, 3.0f};

  SECTION("points can be subtracted to get a vector")
  {
    Point3f q {4.0f, 0.0f, 1.0f};
    Vector3f v {p - q};
    REQUIRE(elem(v, 0) == Approx(0.0f));
    REQUIRE(elem(v, 1) == Approx(1.0f));
    REQUIRE(elem(v, 2) == Approx(2.0f));
  }
}
