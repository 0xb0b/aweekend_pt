#include <catch2/catch.hpp>
#include <math/Vector.h>


TEST_CASE("Vector in 3d space", "[vector]")
{
  Vector3f v {4.0f, 3.0f, 12.0f};

  SECTION("vector's elements can be accessed")
  {
    REQUIRE(x(v) == 4.0f);
    REQUIRE(y(v) == 3.0f);
    REQUIRE(z(v) == 12.0f);
  }

  SECTION("length of the vector can be calculated")
  {
    REQUIRE(norm(v) == Approx(13.0f));
  }

  SECTION("vector is mutable")
  {
    v = Vector3f(1.0f, 2.0f, 3.0f);
    REQUIRE( eq(v, Vector3f(1.0f, 2.0f, 3.0f)) );
  }

  SECTION("vector can be normalized in place")
  {
    const Vector3f original {v};
    normalize_m(v);
    REQUIRE(norm(v) == Approx(1.0f));
    // check that the normalized vector has the direction unchanged
    auto rx = x(original) / x(v);
    auto ry = y(original) / y(v);
    auto rz = z(original) / z(v);
    REQUIRE(rx == Approx(ry));
    REQUIRE(rx == Approx(rz));
  }

  SECTION("normalized vector can be obtained from other vector")
  {
    const auto u { normalize(v) };
    REQUIRE(norm(u) == Approx(1.0f));
    // check that the normalized vector has the direction unchanged
    auto rx = x(u) / x(v);
    auto ry = y(u) / y(v);
    auto rz = z(u) / z(v);
    REQUIRE(rx == Approx(ry));
    REQUIRE(rx == Approx(rz));
  }

  SECTION("zero vector is unchanged if normalized")
  {
    auto u { zero<Vector3f> };

    const auto w { normalize(u) };
    REQUIRE( eq(w, zero<Vector3f>) );

    REQUIRE( eq(normalize_m(u), zero<Vector3f>) );
  }

  SECTION("vectors can be added and subtracted")
  {
    add_m(v, {3.0f, 4.0f, -5.0f});
    REQUIRE( eq(v, Vector3f(7.0f, 7.0f, 7.0f)) );

    sub_m(v, {3.0f, 2.0f, 1.0f});
    REQUIRE( eq(v, Vector3f(4.0f, 5.0f, 6.0f)) );

    {
      const auto u {add(v, Vector3f(0.5f, -0.5f, -1.5f))};
      REQUIRE( eq(u, Vector3f(4.5f, 4.5f, 4.5f)) );
    }

    {
      const auto u {sub(v, Vector3f(0.5f, -0.5f, -1.5f))};
      REQUIRE( eq(u, Vector3f(3.5f, 5.5f, 7.5f)) );
    }
  }

  SECTION("vectors can be multiplied elementwise")
  {
    mul_m(v, {0.5f, 2.0f, 0.25f});
    REQUIRE( eq(v, Vector3f(2.0f, 6.0f, 3.0f)) );

    const auto u {mul(v, Vector3f(2.0f, 0.0f, 4.0f))};
    REQUIRE( eq(u, Vector3f(4.0f, 0.0f, 12.0f)) );
  }

  SECTION("vector can be multiplied by scalar")
  {
    REQUIRE( eq(scale_m(v, 2.0f), Vector3f(8.0f, 6.0f, 24.0f)) );

    const auto u {scale(v, 0.5f)};
    REQUIRE( eq(u, Vector3f(4.0f, 3.0f, 12.0f)) );
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
      REQUIRE( eq(a, k) );
    }
    {
      auto a {cross(k, i)};
      REQUIRE( eq(a, j) );
    }
    {
      auto a {cross(j, k)};
      REQUIRE( eq(a, i) );
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

