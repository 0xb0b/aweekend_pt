#include <catch2/catch.hpp>
#include "math/Vector.h"

TEST_CASE("Vector interface", "[vector]")
{
  Vector3f v {4.0f, 3.0f, 12.0f};

  SECTION("length of the vector can be calculated")
  {
    REQUIRE(norm(v) == Approx(13.0f));
  }

  SECTION("vector can be normalized in place")
  {
    const Vector3f original {v};
    normalize(v);
    REQUIRE(norm(v) == Approx(1.0f));
    // check that the normalized vector has the direction unchanged
    auto rx = original.data[0] / v.data[0];
    auto ry = original.data[1] / v.data[1] ;
    auto rz = original.data[2] / v.data[2];
    REQUIRE(rx == Approx(ry));
    REQUIRE(rx == Approx(rz));
  }

  SECTION("vector's elements can be accessed")
  {
    REQUIRE(elem(v, 0) == Approx(4.0f));
    REQUIRE(elem(v, 1) == Approx(3.0f));
    REQUIRE(elem(v, 2) == Approx(12.0f));
  }

  SECTION("vectors can be added and subtracted")
  {
    v += {3.0f, 4.0f, -5.0f};
    REQUIRE(elem(v, 0) == Approx(7.0f));
    REQUIRE(elem(v, 1) == Approx(elem(v, 0)));
    REQUIRE(elem(v, 2) == Approx(elem(v, 0)));

    v -= {3.0f, 2.0f, 1.0f};
    REQUIRE(elem(v, 0) == Approx(4.0f));
    REQUIRE(elem(v, 1) == Approx(5.0f));
    REQUIRE(elem(v, 2) == Approx(6.0f));

    {
      const auto u {v + Vector3f(0.5f, -0.5f, -1.5f)};
      REQUIRE(elem(u, 0) == Approx(4.5f));
      REQUIRE(elem(u, 1) == Approx(elem(u, 0)));
      REQUIRE(elem(u, 2) == Approx(elem(u, 0)));
    }

    {
      const auto u {v - Vector3f(0.5f, -0.5f, -1.5f)};
      REQUIRE(elem(u, 0) == Approx(3.5f));
      REQUIRE(elem(u, 1) == Approx(5.5f));
      REQUIRE(elem(u, 2) == Approx(7.5f));
    }
  }

  SECTION("vectors can be multiplied elementwise")
  {
    v *= {0.5f, 2.0f, 0.25f};
    REQUIRE(elem(v, 0) == Approx(2.0f));
    REQUIRE(elem(v, 1) == Approx(6.0f));
    REQUIRE(elem(v, 2) == Approx(3.0f));

    const auto u {v * Vector3f(2.0f, 0.0f, 4.0f)};
    REQUIRE(elem(u, 0) == Approx(4.0f));
    REQUIRE(elem(u, 1) == Approx(0.0f));
    REQUIRE(elem(u, 2) == Approx(12.0f));
  }

  SECTION("vector can be multiplied by scalar")
  {
    v *= 2.0f;
    REQUIRE(elem(v, 0) == Approx(8.0f));
    REQUIRE(elem(v, 1) == Approx(6.0f));
    REQUIRE(elem(v, 2) == Approx(24.0f));

    const auto u {0.5f * v};
    REQUIRE(elem(u, 0) == Approx(4.0f));
    REQUIRE(elem(u, 1) == Approx(3.0f));
    REQUIRE(elem(u, 2) == Approx(12.0f));
  }

  SECTION("dot product of vectors can be calculated")
  {
    const Vector3f u {0.2f, 2.0f, 0.5f};
    const auto inner_prod = dot(v, u);
    REQUIRE(inner_prod == Approx(12.8f));
  }

  SECTION("dot product of perpendicular vectors is zero")
  {
    const Vector3f u {0.75f, 2.0f, -0.75f};
    const auto inner_prod = dot(v, u);
    REQUIRE(inner_prod == Approx(0.0f));
  }

  SECTION("dot product of vector by itself is equal to its length squared")
  {
    const auto inner_prod = dot(v, v);
    const auto length = norm(v);
    REQUIRE(inner_prod == Approx(length * length));
  }
}

TEST_CASE("Vector3 cross product", "[vector]")
{
  SECTION("cross product of coordinate system unit vectors")
  {
    Vector3f i {1.0f, 0.0f, 0.0f};
    Vector3f j {0.0f, 1.0f, 0.0f};
    Vector3f k {0.0f, 0.0f, 1.0f};
    {
      auto a {cross(i, j)};
      REQUIRE(elem(a, 0) == Approx(elem(k, 0)));
      REQUIRE(elem(a, 1) == Approx(elem(k, 1)));
      REQUIRE(elem(a, 2) == Approx(elem(k, 2)));
    }
    {
      auto a {cross(k, i)};
      REQUIRE(elem(a, 0) == Approx(elem(j, 0)));
      REQUIRE(elem(a, 1) == Approx(elem(j, 1)));
      REQUIRE(elem(a, 2) == Approx(elem(j, 2)));
    }
    {
      auto a {cross(j, k)};
      REQUIRE(elem(a, 0) == Approx(elem(i, 0)));
      REQUIRE(elem(a, 1) == Approx(elem(i, 1)));
      REQUIRE(elem(a, 2) == Approx(elem(i, 2)));
    }
  }

  SECTION("cross product is perpendicular to input vectors")
  {
    Vector3f v {1.0f, 2.0f, 1.0f};
    Vector3f u {2.0f, 1.0f, -1.0f};
    Vector3f a {cross(u, v)};

    REQUIRE(dot(v, a) == Approx(0.0f));
    REQUIRE(dot(u, a) == Approx(0.0f));
  }
}

