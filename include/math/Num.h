#pragma once

#include <Typeclass.h>


// TODO move to separate place with all typeclasses?

template<typename T>
class Num final : Typeclass
{};


// typeclass instantiation:
// INSTANCE(Num, float)
//
// or by specialization:
// template<typename ElemT>
// struct Instance<Num<Array<ElemT>>> {static constexpr bool value = true;};
//
template<typename T, REQUIRE_INSTANCE(Num, T)>
constexpr T zero = static_cast<T>(0);

template<typename T, REQUIRE_INSTANCE(Num, T)>
constexpr T unit = static_cast<T>(1);


// methods

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator+=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator-=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator*=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator/=(T&, const T&);


template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator+(T a, const T& b)
{
  return a += b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator-(T a, const T& b)
{
  return a -= b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator*(T a, const T& b)
{
  return a *= b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator/(T a, const T& b)
{
  return a /= b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator-(T a)
{
  return zero<T> - a;
}


// primitive types
INSTANCE(Num, int)
INSTANCE(Num, float)

