#pragma once

#include <cmath>
#include "typeclass.h"

// typeclass defines generic behaviour of euclidean vector
class Vector
{};

// define interface for Vector

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T::component_t length(const T& vec)
{
  //auto sum_squared {T::zero}; assumes definition of zero is in Vector type
  // auto sum_squared {T::component_t::zero}; // assumes definition of zero is in Num type
  auto sum_squared {static_cast<T::component_t>(0)}; // no definition of zero
  for (const auto& e : vec.data)
    sum_squared += e * e;
  return std::sqrt(sum_squared);
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
void normalize(T& vec)
{
  // const auto k = T::component_t::one / length(vec);
  const auto k = static_cast<T::component_t>(1) / length(vec);
  for (auto& e : vec.data)
    e *= k;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T::component_t operator[](const T& vec, size_t i)
{
  return vec.data[i];
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T::component_t& operator[](T& vec, size_t i)
{
  return vec.data[i];
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator+=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec[i] += other_vec[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator-=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec[i] -= other_vec[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator+(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec[i] += rhs[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator-(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec[i] -= rhs[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec[i] *= other_vec[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec[i] *= rhs[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(T::component_t s, T& vec)
{
  for (auto& e : vec.data)
    e *= s;
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(T::component_t s, const T& rhs)
{
  T result_vec {rhs};
  for (auto& e : result_vec.data)
    e *= s;
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T::component_t dot(const T& vec1, const T& vec2)
{
  auto result = static_cast<T::component_t>(0);
  for (size_t i = 0; i < T::size; i++)
    result += vec1[i] * vec2[i];
  return result;
}

