#pragma once

#include <math/Array.h>


struct AsColor {};

// RGB color

using Rgb = Array<AsColor, 3, float>

template<>
struct Array<AsColor, 3, float>
{
  std::array<float, 3> data;

  constexpr explicit Array(float s)
    : data {clamp(s, 0.0f, 1.0f), clamp(s, 0.0f, 1.0f), clamp(s, 0.0f, 1.0f)}
  {}

  Array(const Rgb& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Array(float r, float g, float b)
    : data {clamp(r, 0.0f, 1.0f), clamp(g, 0.0f, 1.0f), clamp(b, 0.0f, 1.0f)}
  {}
};


float r(const Rgb& c)
{
  return c.data[0];
}

float g(const Rgb& c)
{
  return c.data[1];
}

float b(const Rgb& c)
{
  return c.data[2];
}


// RGBA color

using Rgba = Array<AsColor, 4, float>

template<>
struct Array<AsColor, 4, float>
{
  std::array<float, 4> data;

  constexpr explicit Array(float s)
    : data {clamp(s, 0.0f, 1.0f), clamp(s, 0.0f, 1.0f), clamp(s, 0.0f, 1.0f),
            1.0f}
  {}

  Array(const Rgb& other, float a)
    : data {other.data[0], other.data[1], other.data[2], clamp(a, 0.0f, 1.0f)}
  {}

  Array(const Rgba& other)
    : data {other.data[0], other.data[1], other.data[2], other.data[3]}
  {}

  Array(float r, float g, float b, float a)
    : data {clamp(r, 0.0f, 1.0f), clamp(g, 0.0f, 1.0f), clamp(b, 0.0f, 1.0f),
            clamp(a, 0.0f, 1.0f)}
  {}
};


float r(const Rgba& c)
{
  return c.data[0];
}

float g(const Rgba& c)
{
  return c.data[1];
}

float b(const Rgba& c)
{
  return c.data[2];
}

float a(const Rgba& c)
{
  return c.data[3];
}

