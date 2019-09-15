#pragma once

#include <array>
#include "typeclass.h"
#include "vector.h"

template<typename S>
struct Vector3
{
  static constexpr size_t size = 3;
  using Scalar = S;

  std::array<Scalar, size> data;
  const Scalar& x;
  const Scalar& y;
  const Scalar& z;

  explicit Vector3(Scalar s)
    : data {s, s, s}
    , x (data[0])
    , y (data[1])
    , z (data[2])
  {}

  Vector3(const Vector3& other)
    : data {other.x, other.y, other.z}
    , x (data[0])
    , y (data[1])
    , z (data[2])
  {}

  Vector3(Scalar s1, Scalar s2, Scalar s3)
    : data {s1, s2, s3}
    , x (data[0])
    , y (data[1])
    , z (data[2])
  {}
};

template<typename S>
Vector3<S> cross(const Vector3<S>& vec1, const Vector3<S>& vec2)
{
  return {vec1.y * vec2.z - vec1.z * vec2.y,
          vec1.z * vec2.x - vec1.x * vec2.z,
          vec1.x * vec2.y - vec1.y * vec2.x};
}

using Vector3f = Vector3<float>;

MAKE_INSTANCE(Vector, Vector3f);

