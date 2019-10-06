#include <catch2/catch.hpp>
#include <math/Point.h>


TEST_CASE("Point in 3d space", "[point]")
{
  Point3f p {4.0f, 1.0f, 3.0f};

  SECTION("vector can be constructed from a point")
  {
    Point3f q {4.0f, 0.0f, 1.0f};
    Vector3f v {toVector(p - q)};
    REQUIRE(v == Vector3f(0.0f, 1.0f, 2.0f));
  }
}

