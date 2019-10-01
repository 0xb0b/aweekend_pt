#pragma once

#include <math/Point.h>
#include <math/Vector.h>


template<size_t dim, typename S>
struct Ray
{
  enum struct Tag : int8_t { primary };

  Tag type;
  Point<dim, S> origin;
  Vector<dim, S> direction;

  explicit Ray(Vector<dim, S> v, Tag t = Tag::primary)
    : type {t}
    , origin {zero<Point<dim, S>>}
    , direction {normalized(v)}
  {}

  Ray(Point<dim, S> p, Vector<dim, S> v, Tag t = Tag::primary)
    : type {t}
    , origin {p}
    , direction {normalized(v)}
  {}

  Ray(Point<dim, S> a, Point<dim, S> b, Tag t = Tag::primary)
    : type {t}
    , origin {a}
    , direction {normalized(b - a)}
  {}
};

using Ray3f = Ray<3, float>;

