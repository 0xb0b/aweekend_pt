#pragma once

#include <cmath>
#include "Array.h"


struct AsVector {};

template<size_t dim, typename ElemT>
using Vector = Array<AsVector, dim, ElemT>;

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;


// Vector specific operations

template<size_t dim, typename ElemT>
ElemT dot(const Vector<dim, ElemT>& a, const Vector<dim, ElemT>& b)
{
  auto result = zero<ElemT>;
  for (size_t i = 0; i < dim; i++)
    add_m(result, mul(a.data[i], b.data[i]));
  return result;
}

template<size_t dim, typename ElemT>
ElemT norm(const Vector<dim, ElemT>& v)
{
  return std::sqrt(dot(v, v));
}

template<size_t dim, typename ElemT>
Vector<dim, ElemT>&
normalize_m(Vector<dim, ElemT>& v)
{
  const auto lsquared = dot(v, v);
  if (lsquared != zero<ElemT>)
    scale_m(v, div(unit<ElemT>, std::sqrt(lsquared)));
  return v;
}

template<size_t dim, typename ElemT>
Vector<dim, ElemT>
normalize(Vector<dim, ElemT> v)
{
  return normalize_m(v);
}


// 3d vector

template<size_t dim, typename ElemT>
ElemT x(const Vector<dim, ElemT>& a)
{
  return a.data[0];
}

template<size_t dim, typename ElemT>
ElemT y(const Vector<dim, ElemT>& a)
{
  return a.data[1];
}

template<size_t dim, typename ElemT>
ElemT z(const Vector<dim, ElemT>& a)
{
  return a.data[2];
}

template<typename ElemT>
Vector<3, ElemT> cross(const Vector<3, ElemT>& a, const Vector<3, ElemT>& b)
{
  return {sub(mul(a.data[1], b.data[2]), mul(a.data[2], b.data[1])),
          sub(mul(a.data[2], b.data[0]), mul(a.data[0], b.data[2])),
          sub(mul(a.data[0], b.data[1]), mul(a.data[1], b.data[0]))};
}

