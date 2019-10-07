#pragma once

#include <math/Array.h>


/* struct Channelf */
// {
  // float value;
// 
  // explicit constexpr Channelf(float c)
    // : value {c}
  // {
    // if (value < 0.0f)
      // value = 0.0f;
    // else if (value > 1.0f)
      // value = 1.0f;
  // }
// 
  // constexpr Channelf(const Channelf& other)
    // : value {other.value}
  // {}
// };
// 
// 
// INSTANCE(Eq, Channelf)
// 
// bool operator==(const Channelf&, const Channelf&);
// 
// 
// INSTANCE(Ord, Channelf)
// 
// bool operator<=(const Channelf&, const Channelf&);
// 
// 
// INSTANCE(Num, Channelf)
// 
// template<>
// constexpr Channelf zero<Channelf> {0.0f};
// 
// template<>
// constexpr Channelf unit<Channelf> {1.0f};
// 
// Channelf& operator+=(Channelf&, const Channelf&);
// 
// Channelf& operator-=(Channelf&, const Channelf&);
// 
// Channelf& operator*=(Channelf&, const Channelf&);
// 
// Channelf& operator/=(Channelf&, const Channelf&);
/*  */

struct AsColor {};

// RGB color
using Color3 = Array<AsColor, 3, float>;

float r(const Color3&);
float g(const Color3&);
float b(const Color3&);

// TODO make Show typeclass?
std::ostream& operator<<(std::ostream&, const Color3&);

// RGBA color
using Color4 = Array<AsColor, 4, float>;

float r(const Color4&);
float g(const Color4&);
float b(const Color4&);
float a(const Color4&);


struct Rgb
{
  uint8_t r;
  uint8_t g;
  uint8_t b;

  explicit Rgb(uint8_t);

  Rgb(uint8_t, uint8_t, uint8_t);

  Rgb(const Rgb&);

  explicit Rgb(const Color3&);

  explicit Rgb(const Color4&);
};


struct Rgba
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  explicit Rgba(uint8_t);

  Rgba(const Rgb&, uint8_t);

  Rgba(uint8_t, uint8_t, uint8_t, uint8_t);

  Rgba(const Rgba&);

  Rgba(const Color3&, uint8_t);

  explicit Rgba(const Color4&);
};

