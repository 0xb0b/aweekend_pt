#include <cmath>
#include <iostream>
#include <light/Color.h>


/* // instance Eq Channelf */
// 
// bool operator==(const Channelf& a, const Channelf& b)
// {
  // return a.value == b.value;
// }
// 
// // instance Ord Channelf
// 
// bool operator<=(const Channelf& a, const Channelf& b)
// {
  // return a.value <= b.value;
// }
// 
// // instance Num Channelf
// 
// Channelf& operator+=(Channelf& a, const Channelf& b)
// {
  // a.value = min(1.0f, a.value + b.value);
  // return a;
// }
// 
// Channelf& operator-=(Channelf& a, const Channelf& b)
// {
  // a.value = max(0.0f, a.value - b.value);
  // return a;
// }
// 
// Channelf& operator*=(Channelf& a, const Channelf& b)
// {
  // a.value *= b.value;
  // return a;
// }
// 
// Channelf& operator/=(Channelf& a, const Channelf& b)
// {
  // if (b.value == 0.0f)
    // a.value = 1.0f;
  // else
    // a.value = min(1.0f, a.value / b.value);
  // return a;
/* } */


// Color3

float r(const Color3& c)
{
  return c.data[0];
}

float g(const Color3& c)
{
  return c.data[1];
}

float b(const Color3& c)
{
  return c.data[2];
}

std::ostream& operator<<(std::ostream& out, const Color3& color)
{
  out << "Color3 (" << r(color) << ", " << g(color) << ", " << b(color) << ")\n";
  return out;
}

// Color4

float r(const Color4& c)
{
  return c.data[0];
}

float g(const Color4& c)
{
  return c.data[1];
}

float b(const Color4& c)
{
  return c.data[2];
}

float a(const Color4& c)
{
  return c.data[3];
}


constexpr auto zero_intensity = static_cast<uint8_t>(0);
constexpr auto full_intensity = static_cast<uint8_t>(255);

// 24 bit RGB color

Rgb::Rgb(uint8_t c)
    : r {clamp(c, zero_intensity, full_intensity)}
    , g {clamp(c, zero_intensity, full_intensity)}
    , b {clamp(c, zero_intensity, full_intensity)}
  {}

Rgb::Rgb(uint8_t red, uint8_t green, uint8_t blue)
    : r {clamp(red, zero_intensity, full_intensity)}
    , g {clamp(green, zero_intensity, full_intensity)}
    , b {clamp(blue, zero_intensity, full_intensity)}
  {}

Rgb::Rgb(const Rgb& other)
    : r {other.r}
    , g {other.g}
    , b {other.b}
  {}

  Rgb::Rgb(const Color3& c)
    : r {static_cast<uint8_t>(std::lround(clamp(::r(c), 0.0f, 1.0f) * 255.0f))}
    , g {static_cast<uint8_t>(std::lround(clamp(::g(c), 0.0f, 1.0f) * 255.0f))}
    , b {static_cast<uint8_t>(std::lround(clamp(::b(c), 0.0f, 1.0f) * 255.0f))}
  {}

  Rgb::Rgb(const Color4& c)
    : r {static_cast<uint8_t>(std::lround(clamp(::r(c), 0.0f, 1.0f) * 255.0f))}
    , g {static_cast<uint8_t>(std::lround(clamp(::g(c), 0.0f, 1.0f) * 255.0f))}
    , b {static_cast<uint8_t>(std::lround(clamp(::b(c), 0.0f, 1.0f) * 255.0f))}
  {}

// 32 bit RGBA color

Rgba::Rgba(uint8_t c)
    : r {clamp(c, zero_intensity, full_intensity)}
    , g {clamp(c, zero_intensity, full_intensity)}
    , b {clamp(c, zero_intensity, full_intensity)}
    , a {clamp(c, zero_intensity, full_intensity)}
  {}

Rgba::Rgba(const Rgb& other, uint8_t alpha)
    : r {other.r}
    , g {other.g}
    , b {other.b}
    , a {clamp(alpha, zero_intensity, full_intensity)}
  {}

Rgba::Rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : r {clamp(red, zero_intensity, full_intensity)}
    , g {clamp(green, zero_intensity, full_intensity)}
    , b {clamp(blue, zero_intensity, full_intensity)}
    , a {clamp(alpha, zero_intensity, full_intensity)}
  {}

Rgba::Rgba(const Rgba& other)
    : r {other.r}
    , g {other.g}
    , b {other.b}
    , a {other.a}
  {}

Rgba::Rgba(const Color3& c, uint8_t alpha)
    : r {static_cast<uint8_t>(std::lround(clamp(::r(c), 0.0f, 1.0f) * 255.0f))}
    , g {static_cast<uint8_t>(std::lround(clamp(::g(c), 0.0f, 1.0f) * 255.0f))}
    , b {static_cast<uint8_t>(std::lround(clamp(::b(c), 0.0f, 1.0f) * 255.0f))}
    , a {clamp(alpha, zero_intensity, full_intensity)}
  {}

Rgba::Rgba(const Color4& c)
    : r {static_cast<uint8_t>(std::lround(clamp(::r(c), 0.0f, 1.0f) * 255.0f))}
    , g {static_cast<uint8_t>(std::lround(clamp(::g(c), 0.0f, 1.0f) * 255.0f))}
    , b {static_cast<uint8_t>(std::lround(clamp(::b(c), 0.0f, 1.0f) * 255.0f))}
    , a {static_cast<uint8_t>(std::lround(clamp(::a(c), 0.0f, 1.0f) * 255.0f))}
  {}

