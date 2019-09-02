#include <catch2/catch.hpp>
#include "math/vector3.h"

TEST_CASE("Vector interface", "[vector]")
{
  Vector3f vec {4.0f, 3.0f, 12.0f};
  // Vector3<int> vec {1, 3, 12};

  SECTION("vector length can be calculated")
  {
    REQUIRE(length(vec) == Approx(13.0f));
  }

  SECTION("vector can be normalized in place")
  {
    Vector3f original_vec {vec};
    normalize(vec);
    REQUIRE(length(vec) == Approx(1.0f));
    // check that normalized vector has the same direction
    auto rx = original_vec.x / vec.x;
    auto ry = original_vec.y / vec.y ;
    auto rz = original_vec.z / vec.z;
    REQUIRE(rx == Approx(ry));
    REQUIRE(rx == Approx(rz));
  }
}

