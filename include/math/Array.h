#pragma once

#include <array>
#include <Eq.h>
#include <Ord.h>
#include <math/Num.h>


template<typename Tag, size_t dim, typename ElemT,
         REQUIRE_INSTANCE(Eq, ElemT), REQUIRE_INSTANCE(Num, ElemT)>
struct Array
{
  std::array<ElemT, dim> data;
};


/* // Mutable interface */
// 
// template<typename Tag, size_t dim, typename ElemT>
// struct Instance<Mutable<Array<Tag, dim, ElemT>>>
// {
  // static constexpr bool value = true;
// };
// 
// // TODO do something with "=" in statements like "for (size_t i = 0; i < 10; i++)" ?
// // like:
// // loop(0, dim, [&](size_t i)
// //   {
// //     a.data[i] << b.data[i];
// //     return true;
// //   })
// //
// // how to break from this? return bool continue_iteration from lambda?
// // void loop(size_t start, size_t stop, std::function<bool(size_t)> func)
// // {
// //   auto continue_iteration = true;
// //   for (size_t i = start; i < stop && continue_iteration; i++)
// //   {
// //     continue_iteration = func(i);
// //   }
// // }
// 
// template<typename Tag, size_t dim, typename ElemT>
// Array<Tag, dim, ElemT>&
// operator<<(Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
// {
  // for (size_t i = 0; i < dim; i++)
    // a.data[i] << b.data[i];
  // return a;
/* } */


// Eq interface

template<typename Tag, size_t dim, typename ElemT>
struct Instance<Eq<Array<Tag, dim, ElemT>>>
{
  static constexpr bool value = true;
};

template<typename Tag, size_t dim, typename ElemT>
bool operator==(const Array<Tag, dim, ElemT>& a,
                const Array<Tag, dim, ElemT>& b)
{
  for (size_t i = 0; i < dim; i++)
    if (a.data[i] != b.data[i])
      return false;
  return true;
}


// Num interface

template<typename Tag, size_t dim, typename ElemT>
struct Instance<Num<Array<Tag, dim, ElemT>>>
{
  static constexpr bool value = true;
};

// constants require constructor
//   constexpr explicit Array(ElemT x);
// and constexpr copy constructor for ElemT

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT>
zero<Array<Tag, dim, ElemT> > {zero<ElemT>};

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT>
unit<Array<Tag, dim, ElemT> > {unit<ElemT>};


template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator+=(Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  for (size_t i = 0; i < dim; i++)
    a.data[i] += b.data[i];
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator-=(Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  for (size_t i = 0; i < dim; i++)
    a.data[i] -= b.data[i];
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator*=(Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  for (size_t i = 0; i < dim; i++)
    a.data[i] *= b.data[i];
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator/=(Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  // TODO division by zero?
  for (size_t i = 0; i < dim; i++)
    a.data[i] /= b.data[i];
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator-(Array<Tag, dim, ElemT> a)
{
  for (size_t i = 0; i < dim; i++)
    a.data[i] = -a.data[i];
  return a;
}


// multiplication by a scalar

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
scale_m(Array<Tag, dim, ElemT>& a, ElemT s)
{
  for (auto& e : a.data)
    e *= s;
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
scale(Array<Tag, dim, ElemT> a, ElemT s)
{
  return scale_m(a, s);
}


// linear interpolation
// result is equal to b if blend coefficient k is 1 and to a if k is 0
template<typename Tag, size_t dim, typename ElemT, REQUIRE_INSTANCE(Ord, ElemT)>
Array<Tag, dim, ElemT>
mix(Array<Tag, dim, ElemT> a, const Array<Tag, dim, ElemT>& b, ElemT k)
{
  const auto kb {clamp(k, zero<ElemT>, unit<ElemT>)};
  const auto ka {unit<ElemT> - k};
  for (size_t i = 0; i < dim; i++)
    a.data[i] = ka * a.data[i] + kb * b.data[i];
  return a;
}


// define constructors for 3d Array and 4d Array

template<typename Tag, typename ElemT>
struct Array<Tag, 3, ElemT>
{
  std::array<ElemT, 3> data;

  constexpr explicit Array(ElemT s)
    : data {s, s, s}
  {}

  Array(const Array<Tag, 3, ElemT>& other)
    : data {other.data[0], other.data[1], other.data[2]}
  {}

  Array(ElemT x, ElemT y, ElemT z)
    : data {x, y, z}
  {}
};

template<typename Tag, typename ElemT>
struct Array<Tag, 4, ElemT>
{
  std::array<ElemT, 4> data;

  constexpr explicit Array(ElemT s)
    : data {s, s, s, s}
  {}

  Array(const Array<Tag, 3, ElemT>& other, ElemT w)
    : data {other.data[0], other.data[1], other.data[2], w}
  {}

  Array(const Array<Tag, 4, ElemT>& other)
    : data {other.data[0], other.data[1], other.data[2], other.data[3]}
  {}

  Array(ElemT x, ElemT y, ElemT z, ElemT w)
    : data {x, y, z, w}
  {}
};

