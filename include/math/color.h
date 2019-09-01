#pragma once

#include <array>
#include "typeclass.h"
#include "vector.h"

template<typename S>
struct Rgb
{
  static constexpr size_t size = 3;
  using Scalar = S;
  std::array<Scalar, size> data;
  const Scalar& r;
  const Scalar& g;
  const Scalar& b;

  explicit Rgb(Scalar s)
    : data {s, s, s}
    , r (data[0])
    , g (data[1])
    , b (data[2])
  {}

  Rgb(const Rgb& other)
    : data {other.r, other.g, other.b}
    , r (data[0])
    , g (data[1])
    , b (data[2])
  {}

  Rgb(Scalar s1, Scalar s2, Scalar s3)
    : data {s1, s2, s3}
    , r (data[0])
    , g (data[1])
    , b (data[2])
  {}
};

using Color3f = Rgb<float>;
INSTANCE(Vector, Color3f);

