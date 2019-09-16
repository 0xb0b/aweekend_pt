#pragma once

#include <cmath>
#include "Array.h"
#include "Vector.h"

struct PointTag
{};

template<size_t dim, typename T>
using Point = Array<PointTag, dim, T>;

// Point interface

template<size_t dim, typename T>
Point<dim, T>& operator+=(Point<dim, T>& p, const Vector<dim, T>& v)
{
  for (size_t i = 0; i < dim; i++)
    p.data[i] += v.data[i];
  return p;
}

template<size_t dim, typename T>
Point<dim, T>& operator-=(Point<dim, T>& p, const Vector<dim, T>& v)
{
  for (size_t i = 0; i < dim; i++)
    p.data[i] -= v.data[i];
  return p;
}

template<size_t dim, typename T>
Point<dim, T> operator+(const Point<dim, T>& p, const Vector<dim, T>& v)
{
  auto result {p};
  for (size_t i = 0; i < dim; i++)
    result.data[i] += v.data[i];
  return result;
}

template<size_t dim, typename T>
Point<dim, T> operator-(const Point<dim, T>& p, const Vector<dim, T>& v)
{
  auto result {p};
  for (size_t i = 0; i < dim; i++)
    result.data[i] -= v.data[i];
  return result;
}

// TODO have to define vector from point construction
/*
template<size_t dim, typename T>
Vector<dim, T> operator-(const Point<dim, T>& a, const Point<dim, T>& b)
{
  Vector<dim, T> result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] -= b.data[i];
  return result;
}
*/

template<size_t dim, typename T>
T distance(const Point<dim, T>& a, const Point<dim, T>& b)
{
  T d_squared = static_cast<T>(0);
  for (size_t i = 0; i < dim; i++)
  {
    const auto d = a.data[i] - b.data[i];
    d_squared += d * d;
  }
  return std::sqrt(d_squared);
}


template<typename T>
struct Array<PointTag, 3, T>
{
  std::array<T, 3> data;

  explicit Array(T s)
    : data {s, s, s}
  {}

  Array(const Point<3, T>& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Array(T x, T y, T z)
    : data {x, y, z}
  {}
};

using Point3f = Point<3, float>;

