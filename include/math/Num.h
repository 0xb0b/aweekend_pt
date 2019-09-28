#pragma once

#include <Typeclass.h>


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

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator+=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator+(const T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator-=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator-(const T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator-(const T& a)
{
  return zero<T> - a;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& operator*=(T&, const T&);

template<typename T, REQUIRE_INSTANCE(Num, T)>
T operator*(const T&, const T&);


INSTANCE(Num, int)

INSTANCE(Num, float)

