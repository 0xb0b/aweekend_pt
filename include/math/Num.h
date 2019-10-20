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
T& add_m(T& a, const T& b)
{
  return a += b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& sub_m(T& a, const T& b)
{
  return a -= b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& mul_m(T& a, const T& b)
{
  return a *= b;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& div_m(T& a, const T& b)
{
  return a /= b;
}


template<typename T, REQUIRE_INSTANCE(Num, T)>
T add(T a, const T& b)
{
  return add_m(a, b);
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T sub(T a, const T& b)
{
  return sub_m(a, b);
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T mul(T a, const T& b)
{
  return mul_m(a, b);
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T div(T a, const T& b)
{
  return div_m(a, b);
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T& negate_m(T& a)
{
  a = sub(zero<T>, a);
  return a;
}

template<typename T, REQUIRE_INSTANCE(Num, T)>
T negate(T a)
{
  return negate_m(a);
}


// primitive types
INSTANCE(Num, int)
INSTANCE(Num, float)

