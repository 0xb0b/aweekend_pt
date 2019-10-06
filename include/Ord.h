#pragma once

#include <cstdint>
#include <Typeclass.h>


template<typename T, REQUIRE_INSTANCE(Eq, T)>
class Ord final : Typeclass
{};


// methods

template<typename T, REQUIRE_INSTANCE(Ord, T)>
bool operator<=(const T&, const T&);

template<typename T, REQUIRE_INSTANCE(Ord, T)>
bool operator>=(const T& a, const T& b)
{
  return !(a <= b) || a == b;
}

template<typename T, REQUIRE_INSTANCE(Ord, T)>
bool operator<(const T& a, const T& b)
{
  return (a <= b) && a != b;
}

template<typename T, REQUIRE_INSTANCE(Ord, T)>
bool operator>(const T& a, const T& b)
{
  return !(a <= b);
}

template<typename T, REQUIRE_INSTANCE(Ord, T)>
T max(const T& a, const T& b)
{
  return (a >= b) ? a : b;
}

template<typename T, REQUIRE_INSTANCE(Ord, T)>
T min(const T& a, const T& b)
{
  return (a <= b) ? a : b;
}

template<typename T, REQUIRE_INSTANCE(Ord, T)>
T clamp(const T& a, const T& lower, const T& upper)
{
  return max(lower, min(upper, a));
}


// primitive types
INSTANCE(Ord, int)
INSTANCE(Ord, uint8_t)
INSTANCE(Ord, float)

