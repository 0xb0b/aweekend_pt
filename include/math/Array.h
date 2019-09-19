#pragma once

#include <array>

template<typename Tag, size_t dim, typename ElemT>
struct Array
{
  std::array<ElemT, dim> data;
};


template<typename Tag, size_t dim, typename ElemT>
ElemT elem(const Array<Tag, dim, ElemT>& a, size_t i)
{
  return a.data[i];
}


// arithmetic operations

template<typename Tag, size_t dim, typename ElemT>
Array<Tag, dim, ElemT>&
operator+=(Array<Tag, dim, ElemT>& this_a, const Array<Tag, dim, ElemT>& that_a)
{
  for (size_t i = 0; i < dim; i++)
    this_a.data[i] += that_a.data[i];
  return this_a;
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
operator+(const Array<Tag, dim, ElemT>& a, const Array<Tag, dim, ElemT>& b)
{
  auto result {a};
  for (size_t i = 0; i < dim; i++)
    result.data[i] += b.data[i];
  return result;
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

