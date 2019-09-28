#pragma once

#include <cmath>
#include <math/Vector.h>
#include <math/Point.h>

template<size_t dim, typename S>
struct Ray
{
  Point<dim, S> origin;
  Vector<dim, S> direction;

  Ray(Point<dim, S> p, Vector<dim, S> v)
    : origin {p}
    , direction {v}
  {
    lsquared = dot(v, v);
    if (lsquared > zero<S>)
      direction /= std::sqrt(lsquared);
  }

  Ray(Point<dim, S> a, Point<dim, S> b)
    : origin {a}
    , direction {b - a}
  {
    lsquared = dot(v, v);
    if (lsquared > zero<S>)
      direction /= std::sqrt(lsquared);
  }
};

using Ray3f = Ray<3, float>;

