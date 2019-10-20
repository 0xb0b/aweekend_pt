#pragma once

#include <cstdint>
#include <Typeclass.h>

// TODO is it really needed?
// there are problems e.g. range-based for requires instance Eq for iterators comparison
// maybe stay with the standard c++ way of treating equality?

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

