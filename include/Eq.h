#pragma once

#include <Typeclass.h>


template<typename T>
class Eq final : Typeclass
{};

template<typename T, REQUIRE_INSTANCE(Eq, T)>
bool operator==(const T&, const T&);

template<typename T, REQUIRE_INSTANCE(Eq, T)>
bool operator!=(const T& a, const T& b)
{
  return !(a == b);
}


INSTANCE(Eq, int)

// TODO approximate equality for floats?
INSTANCE(Eq, float)

