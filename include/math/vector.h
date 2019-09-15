#pragma once

#include <cmath>
#include <array>

/* typeclass implementation, looks like overkill for vector

#include <typeclass.h>

// what if there is some other generic function with the same name in scope?
// error: call to 'length' is ambiguous
// template<typename T>
// int length(const T& x)
// {
  // return 0;
// }

// what if another typeclass has the same function?
// error: template parameter redefines default argument
// error: redefinition of 'length'
// class Vectorint
// {};
// 
// template<typename T, REQUIRE_INSTANCE(Vectorint, T)>
// typename T::Scalar length(const T& vec)
// {
  // auto sum {static_cast<typename T::Scalar>(0)}; // no definition of zero
  // for (const auto& e : vec.data)
    // sum += e;
  // return sum;
// }

// typeclass defines generic behaviour of euclidean vector
class Vector
{};

// Vector interface
// in fact the following are also the parts of the interface (?):
//   - Vector instance X has to have members X::data and X::size and type definition X::Scalar
//   - X::data member has to have operator[] defined
// the requirement for the operator[] can be removed by replacing requirement for the data member
// by the requirement for the data access method(s)

// TODO assignment operator (?)
// TODO equality operator (?)

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar dot(const T& a, const T& b)
{
  auto result = static_cast<typename T::Scalar>(0);
  for (size_t i = 0; i < T::size; i++)
    result += a.data[i] * b.data[i];
  return result;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar norm(const T& v)
{
  return std::sqrt(dot(v, v));
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
void normalize(T& v)
{
  // TODO check for zero length?
  // const auto k = T::Scalar::one / length(vec);
  const auto k = static_cast<typename T::Scalar>(1) / norm(v);
  for (auto& e : v.data)
    e *= k;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar elem(const T& v, size_t i)
{
  return v.data[i];
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator+=(T& this_v, const T& other_v)
{
  for (size_t i = 0; i < T::size; i++)
    this_v.data[i] += other_v.data[i];
  return this_v;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator-=(T& this_v, const T& other_v)
{
  for (size_t i = 0; i < T::size; i++)
    this_v.data[i] -= other_v.data[i];
  return this_v;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator+(const T& a, const T& b)
{
  T result {a};
  for (size_t i = 0; i < T::size; i++)
    result.data[i] += b.data[i];
  return result;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator-(const T& a, const T& b)
{
  T result {a};
  for (size_t i = 0; i < T::size; i++)
    result.data[i] -= b.data[i];
  return result;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(T& this_v, const T& other_v)
{
  for (size_t i = 0; i < T::size; i++)
    this_v.data[i] *= other_v.data[i];
  return this_v;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(const T& a, const T& b)
{
  T result {a};
  for (size_t i = 0; i < T::size; i++)
    result.data[i] *= b.data[i];
  return result;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(T& v, typename T::Scalar s)
{
  for (auto& e : v.data)
    e *= s;
  return v;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(typename T::Scalar s, const T& v)
{
  T result {v};
  for (auto& e : result.data)
    e *= s;
  return result;
}
*/

template<size_t dim, typename T>
struct Vector
{
  std::array<T, dim> data;
};

// Vector interface

template<size_t dim, typename T>
T dot(const Vector<dim, T>& a, const Vector<dim, T>& b)
{
  auto result = static_cast<T>(0);
  for (size_t i = 0; i < dim; i++)
    result += a.data[i] * b.data[i];
  return result;
}

template<size_t dim, typename T>
T norm(const Vector<dim, T>& v)
{
  return std::sqrt(dot(v, v));
}

template<size_t dim, typename T>
void normalize(Vector<dim, T>& v)
{
  // TODO check for zero length?
  // const auto k = T::Scalar::one / length(vec);
  const auto k = static_cast<T>(1) / norm(v);
  for (auto& e : v.data)
    e *= k;
}

template<size_t dim, typename T>
T elem(const Vector<dim, T>& v, size_t i)
{
  return v.data[i];
}

template<size_t dim, typename T>
Vector<dim, T>& operator+=(Vector<dim, T>& this_v, const Vector<dim, T>& other_v)
{
  for (size_t i = 0; i < dim; i++)
    this_v.data[i] += other_v.data[i];
  return this_v;
}

template<size_t dim, typename T>
Vector<dim, T>& operator-=(Vector<dim, T>& this_v, const Vector<dim, T>& other_v)
{
  for (size_t i = 0; i < dim; i++)
    this_v.data[i] -= other_v.data[i];
  return this_v;
}

template<size_t dim, typename T>
Vector<dim, T> operator+(const Vector<dim, T>& a, const Vector<dim, T>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] += b.data[i];
  return result;
}

template<size_t dim, typename T>
Vector<dim, T> operator-(const Vector<dim, T>& a, const Vector<dim, T>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] -= b.data[i];
  return result;
}

template<size_t dim, typename T>
Vector<dim, T>& operator*=(Vector<dim, T>& this_v, const Vector<dim, T>& other_v)
{
  for (size_t i = 0; i < dim; i++)
    this_v.data[i] *= other_v.data[i];
  return this_v;
}

template<size_t dim, typename T>
Vector<dim, T> operator*(const Vector<dim, T>& a, const Vector<dim, T>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] *= b.data[i];
  return result;
}

template<size_t dim, typename T>
Vector<dim, T>& operator*=(Vector<dim, T>& v, T s)
{
  for (auto& e : v.data)
    e *= s;
  return v;
}

template<size_t dim, typename T>
Vector<dim, T> operator*(T s, const Vector<dim, T>& v)
{
  auto result {v};
  for (auto& e : result.data)
    e *= s;
  return result;
}

template<typename T>
struct Vector<3, T>
{
  std::array<T, 3> data;

  explicit Vector(T s)
    : data {s, s, s}
  {}

  Vector(const Vector& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Vector(T s1, T s2, T s3)
    : data {s1, s2, s3}
  {}
};

template<typename T>
Vector<3, T> cross(const Vector<3, T>& a, const Vector<3, T>& b)
{
  return {a.data[1] * b.data[2] - a.data[2] * b.data[1],
          a.data[2] * b.data[0] - a.data[0] * b.data[2],
          a.data[0] * b.data[1] - a.data[1] * b.data[0]};
}

using Vector3f = Vector<3, float>;

