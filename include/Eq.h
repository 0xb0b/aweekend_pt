#pragma once

#include <cstdint>
#include <Typeclass.h>


template<typename T>
class Eq final : Typeclass
{};


// methods

template<typename T, REQUIRE_INSTANCE(Eq, T)>
bool operator==(const T&, const T&);

template<typename T, REQUIRE_INSTANCE(Eq, T)>
bool operator!=(const T& a, const T& b)
{
  return !(a == b);
}


// primitive types
INSTANCE(Eq, int)
INSTANCE(Eq, uint8_t)
// TODO approximate equality for floats?
INSTANCE(Eq, float)

