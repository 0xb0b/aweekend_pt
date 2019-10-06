#pragma once

#include <utility>
#include <Typeclass.h>


template<typename T>
class Mutable final : Typeclass
{};


// methods

// "=" assignment operator can not overloaded as a free function
// due to the idiotic decision to default generate assignment even if no one asked for that
// this means a separate function has to be provided for bit shifting when needed
template<typename T, REQUIRE_INSTANCE(Mutable, T)>
T& operator<<(T&, const T&)
{
  return a = b;
}


// primitive types
INSTANCE(Mutable, int)
INSTANCE(Mutable, float)

