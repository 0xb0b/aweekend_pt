#pragma once

#include <cmath>
#include <math/Array.h>
#include <math/Vector.h>


struct AsPoint {};

template<size_t dim, typename ElemT>
using Point = Array<AsPoint, dim, ElemT>;

using Point3f = Point<3, float>;


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

