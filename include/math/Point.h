#pragma once

#include <cmath>
#include <math/Array.h>
#include <math/Vector.h>


struct AsPoint {};

template<size_t dim, typename ElemT>
using Point = Array<AsPoint, dim, ElemT>;

using Point3f = Point<3, float>;


// construct Point from Vector

template<size_t dim, typename ElemT>
Point<dim, ElemT>
toPoint(const Vector<dim, ElemT>& v)
{
  auto result {zero<Point<dim, ElemT>>};
  for (size_t i = 0; i < dim; i++)
    result.data[i] = v.data[i];
  return result;
}

// construct Vector from Point

template<size_t dim, typename ElemT>
Vector<dim, ElemT>
toVector(const Point<dim, ElemT>& p)
{
  auto result {zero<Vector<dim, ElemT>>};
  for (size_t i = 0; i < dim; i++)
    result.data[i] = p.data[i];
  return result;
}


// translate Point by Vector

template<size_t dim, typename ElemT>
Point<dim, ElemT>&
translate_m(Point<dim, ElemT>& p, const Vector<dim, ElemT>& v)
{
  for (size_t i = 0; i < dim; i++)
    add_m(p.data[i], v.data[i]);
  return p;
}

template<size_t dim, typename ElemT>
Point<dim, ElemT>
translate(Point<dim, ElemT> p, const Vector<dim, ElemT>& v)
{
  return translate_m(p, v);
}

template<size_t dim, typename ElemT>
ElemT distance2(const Point<dim, ElemT>& a, const Point<dim, ElemT>& b)
{
  auto d_squared = zero<ElemT>;
  for (size_t i = 0; i < dim; i++)
  {
    auto d = sub(a.data[i], b.data[i]);
    add_m(d_squared, mul_m(d, d));
  }
  return d_squared;
}

template<size_t dim, typename ElemT>
ElemT distance(const Point<dim, ElemT>& a, const Point<dim, ElemT>& b)
{
  return std::sqrt(distance2(a, b));
}

// 3d point

template<size_t dim, typename ElemT>
ElemT x(const Point<dim, ElemT>& p)
{
  return p.data[0];
}

template<size_t dim, typename ElemT>
ElemT y(const Point<dim, ElemT>& p)
{
  return p.data[1];
}

template<size_t dim, typename ElemT>
ElemT z(const Point<dim, ElemT>& p)
{
  return p.data[2];
}

