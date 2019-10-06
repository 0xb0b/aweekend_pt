#pragma once

#include <math/Point.h>
#include <math/Vector.h>


struct Ray
{
  enum struct Tag : int8_t { primary };

  Tag type;
  Point3f origin;
  Vector3f direction;

  explicit Ray(Vector3f v, Tag t = Tag::primary)
    : type {t}
    , origin {zero<Point3f>}
    , direction {normalize_m(v)}
  {}

  Ray(Point3f p, Vector3f v, Tag t = Tag::primary)
    : type {t}
    , origin {p}
    , direction {normalize_m(v)}
  {}

  Ray(Point3f a, Point3f b, Tag t = Tag::primary)
    : type {t}
    , origin {a}
    , direction {normalize(toVector(b - a))}
  {}
};

