#pragma once

#include <array>
#include "Num.h"

template<typename Tag, size_t dim, typename ElemT, REQUIRE_INSTANCE(Num, ElemT)>
struct Array
{
  std::array<ElemT, dim> data;
};

INSTANCE_TEMPLATE(Num, Array<Tag, dim, ElemT>, template<typename Tag, size_t dim, typename ElemT>)


// Num interface

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT> zero {};

template<typename Tag, size_t dim, typename ElemT>
constexpr Array<Tag, dim, ElemT> unit {unit<ElemT>};


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


// multiplication by scalar

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

