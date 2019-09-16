#pragma once

#include <array>

template<typename Tag, size_t dim, typename T>
struct Array
{
  std::array<T, dim> data;
};


template<typename Tag, size_t dim, typename T>
T elem(const Array<Tag, dim, T>& a, size_t i)
{
  return a.data[i];
}

