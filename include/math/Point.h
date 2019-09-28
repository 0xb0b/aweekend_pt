#pragma once

#include <cmath>
#include "Array.h"
#include "Vector.h"

struct AsPoint {};

template<size_t dim, typename ElemT>
using Point = Array<AsPoint, dim, ElemT>;


// translate Point by Vector

template<size_t dim, typename ElemT>
Point<dim, ElemT>&
operator+=(Point<dim, ElemT>& p, const Vector<dim, ElemT>& v)
{
  for (size_t i = 0; i < dim; i++)
    p.data[i] += v.data[i];
  return p;
}

template<size_t dim, typename ElemT>
Point<dim, ElemT>&
operator-=(Point<dim, ElemT>& p, const Vector<dim, ElemT>& v)
{
  for (size_t i = 0; i < dim; i++)
    p.data[i] -= v.data[i];
  return p;
}

template<size_t dim, typename ElemT>
Point<dim, ElemT>
operator+(const Point<dim, ElemT>& p, const Vector<dim, ElemT>& v)
{
  auto result {p};
  for (size_t i = 0; i < dim; i++)
    result.data[i] += v.data[i];
  return result;
}

template<size_t dim, typename ElemT>
Point<dim, ElemT>
operator-(const Point<dim, ElemT>& p, const Vector<dim, ElemT>& v)
{
  auto result {p};
  for (size_t i = 0; i < dim; i++)
    result.data[i] -= v.data[i];
  return result;
}


// Vector connecting two Points

template<size_t dim, typename ElemT>
Vector<dim, ElemT>
operator-(const Point<dim, ElemT>& a, const Point<dim, ElemT>& b)
{
  auto result {zero<Vector<dim, ElemT>>};
  for (size_t i = 0; i < dim; i++)
    result.data[i] = a.data[i] - b.data[i];
  return result;
}


template<size_t dim, typename ElemT>
ElemT distance(const Point<dim, ElemT>& a, const Point<dim, ElemT>& b)
{
  auto d_squared = zero<ElemT>;
  for (size_t i = 0; i < dim; i++)
  {
    const auto d = a.data[i] - b.data[i];
    d_squared += d * d;
  }
  return std::sqrt(d_squared);
}


// 3d point

template<typename ElemT>
struct Array<AsPoint, 3, ElemT>
{
  std::array<ElemT, 3> data;

  explicit Array(ElemT s)
    : data {s, s, s}
  {}

  Array(const Point<3, ElemT>& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Array(ElemT x, ElemT y, ElemT z)
    : data {x, y, z}
  {}
};

using Point3f = Point<3, float>;

