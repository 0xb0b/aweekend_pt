#pragma once

#include <math/Vector.h>
#include <math/Point.h>


template<size_t dim, typename S>
struct Ray
{
  Point<dim, S> origin;
  Vector<dim, S> direction;

  explicit Ray(Vector<dim, S> v)
    : origin {zero<Point<dim, S>>}
    , direction {normalized(v)}
  {}

  Ray(Point<dim, S> p, Vector<dim, S> v)
    : origin {p}
    , direction {normalized(v)}
  {}

  Ray(Point<dim, S> a, Point<dim, S> b)
    : origin {a}
    , direction {normalized(b - a)}
  {}
};

using Ray3f = Ray<3, float>;

