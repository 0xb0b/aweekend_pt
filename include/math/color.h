#include <array>
#include "typeclass.h"
#include "vector.h"

template<typename S>
struct Rgb
{
  static constexpr size_t size = 3;
  using component_t = S;
  std::array<component_t, size> data;
  const component_t& r;
  const component_t& g;
  const component_t& b;

  explicit Rgb(component_t s)
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

  Rgb(component_t s1, component_t s2, component_t s3)
    : data {s1, s2, s3}
    , r (data[0])
    , g (data[1])
    , b (data[2])
  {}
};

using Color3f = Rgb<float>;
INSTANCE(Vector, Color3f);

