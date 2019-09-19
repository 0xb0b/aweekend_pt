#pragma once

#include <cmath>
#include "Array.h"

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

struct AsVector
{};

template<size_t dim, typename ElemT>
using Vector = Array<AsVector, dim, ElemT>;


// Vector interface

template<size_t dim, typename ElemT>
ElemT dot(const Vector<dim, ElemT>& a, const Vector<dim, ElemT>& b)
{
  auto result = static_cast<ElemT>(0);
  for (size_t i = 0; i < dim; i++)
    result += a.data[i] * b.data[i];
  return result;
}

template<size_t dim, typename ElemT>
ElemT norm(const Vector<dim, ElemT>& v)
{
  return std::sqrt(dot(v, v));
}

template<size_t dim, typename ElemT>
void normalize(Vector<dim, ElemT>& v)
{
  // TODO check for zero length?
  const auto k = static_cast<ElemT>(1) / norm(v);
  v *= k;
}


template<typename ElemT>
struct Array<AsVector, 3, ElemT>
{
  std::array<ElemT, 3> data;

  Array()
    : data {static_cast<ElemT>(0), static_cast<ElemT>(0), static_cast<ElemT>(0)}
  {}

  explicit Array(ElemT s)
    : data {s, s, s}
  {}

  Array(const Vector<3, ElemT>& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Array(ElemT x, ElemT y, ElemT z)
    : data {x, y, z}
  {}
};

template<typename ElemT>
ElemT x(const Vector<3, ElemT>& a)
{
  return a.data[0];
}

template<typename ElemT>
ElemT y(const Vector<3, ElemT>& a)
{
  return a.data[1];
}

template<typename ElemT>
ElemT z(const Vector<3, ElemT>& a)
{
  return a.data[2];
}

template<typename ElemT>
Vector<3, ElemT> cross(const Vector<3, ElemT>& a, const Vector<3, ElemT>& b)
{
  return {y(a) * z(b) - z(a) * y(b),
          z(a) * x(b) - x(a) * z(b),
          x(a) * y(b) - y(a) * x(b)};
}

using Vector3f = Vector<3, float>;

