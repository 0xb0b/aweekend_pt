#pragma once

#include <Typeclass.h>


template<typename T, REQUIRE_INSTANCE(Eq, T)>
class Ord final : Typeclass
{};


template<typename T, REQUIRE_INSTANCE(Ord, T)>
bool operator<=(const T& a, const T& b);

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


INSTANCE(Ord, int)

INSTANCE(Ord, float)

