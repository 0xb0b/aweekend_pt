#pragma once

#include <array>
#include <Eq.h>
#include <math/Num.h>


template<typename Tag, size_t dim, typename ElemT,
         REQUIRE_INSTANCE(Eq, ElemT), REQUIRE_INSTANCE(Num, ElemT)>
struct Array
{
  std::array<ElemT, dim> data;
};

template<typename Tag, size_t dim, typename ElemT>
struct Instance<Eq<Array<Tag, dim, ElemT> > >
{
  static constexpr bool value = true;
};

template<typename Tag, size_t dim, typename ElemT>
struct Instance<Num<Array<Tag, dim, ElemT> > >
{
  static constexpr bool value = true;
};


// Eq interface

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

// constants require constructor
//   constexpr explicit Array(ElemT x);

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT>
zero<Array<Tag, dim, ElemT> > {zero<ElemT>};

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT>
unit<Array<Tag, dim, ElemT> > {unit<ElemT>};


template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator+=(Array<Tag, dim, ElemT>& this_a, const Array<Tag, dim, ElemT>& that_a)
{
  for (size_t i = 0; i < dim; i++)
    this_a.data[i] += that_a.data[i];
  return this_a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator+(const Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] += b.data[i];
  return result;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator-=(Array<Tag, dim, ElemT>& this_a, const Array<Tag, dim, ElemT>& that_a)
{
  for (size_t i = 0; i < dim; i++)
    this_a.data[i] -= that_a.data[i];
  return this_a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator-(const Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] -= b.data[i];
  return result;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator*=(Array<Tag, dim, ElemT>& this_a, const Array<Tag, dim, ElemT>& that_a)
{
  for (size_t i = 0; i < dim; i++)
    this_a.data[i] *= that_a.data[i];
  return this_a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator*(const Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] *= b.data[i];
  return result;
}


// multiplication by a scalar

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator*=(Array<Tag, dim, ElemT>& a, ElemT s)
{
  for (auto& e : a.data)
    e *= s;
  return a;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator*(ElemT s, const Array<Tag, dim, ElemT>& a)
{
  auto result {a};
  for (auto& e : result.data)
    e *= s;
  return result;
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator/=(Array<Tag, dim, ElemT>& a, ElemT s)
{
  return a *= (unit<ElemT> / s);
}

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>
operator/(const Array<Tag, dim, ElemT>& a, ElemT s)
{
  return (unit<ElemT> / s) * a;
}


// define constructors for 3d Array

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
