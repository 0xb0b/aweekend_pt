#include <array>
#include "typeclass.h"
#include "vector.h"

template<typename S>
struct Vector3
{
  static constexpr size_t size = 3;
  using component_t = S;

  std::array<component_t, size> data;
  const component_t& x;
  const component_t& y;
  const component_t& z;

  explicit Vector3(component_t s)
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

  Vector3(component_t s1, component_t s2, component_t s3)
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
INSTANCE(Vector, Vector3f);

