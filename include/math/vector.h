#pragma once

#include <cmath>
#include <typeclass.h>

// typeclass defines generic behaviour of euclidean vector
class Vector
{};

// define interface for Vector

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar length(const T& vec)
{
  //auto sum_squared {T::zero}; assumes definition of zero is in Vector type
  // auto sum_squared {T::Scalar::zero}; // assumes definition of zero is in Num type
  auto sum_squared {static_cast<typename T::Scalar>(0)}; // no definition of zero
  for (const auto& e : vec.data)
    sum_squared += e * e;
  return std::sqrt(sum_squared);
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
void normalize(T& vec)
{
  // const auto k = T::Scalar::one / length(vec);
  const auto k = static_cast<typename T::Scalar>(1) / length(vec);
  for (auto& e : vec.data)
    e *= k;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar elem(const T& vec, size_t i)
{
  return vec.data[i];
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar& elem(T& vec, size_t i)
{
  return vec.data[i];
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator+=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec.data[i] += other_vec.data[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator-=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec.data[i] -= other_vec.data[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator+(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec.data[i] += rhs.data[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator-(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec.data[i] -= rhs.data[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(T& vec, const T& other_vec)
{
  for (size_t i = 0; i < T::size; i++)
    vec.data[i] *= other_vec.data[i];
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(const T& lhs, const T& rhs)
{
  T result_vec {lhs};
  for (size_t i = 0; i < T::size; i++)
    result_vec.data[i] *= rhs.data[i];
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T& operator*=(typename T::Scalar s, T& vec)
{
  for (auto& e : vec.data)
    e *= s;
  return vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
T operator*(typename T::Scalar s, const T& rhs)
{
  T result_vec {rhs};
  for (auto& e : result_vec.data)
    e *= s;
  return result_vec;
}

template<typename T, REQUIRE_INSTANCE(Vector, T)>
typename T::Scalar dot(const T& vec1, const T& vec2)
{
  auto result = static_cast<typename T::Scalar>(0);
  for (size_t i = 0; i < T::size; i++)
    result += vec1.data[i] * vec2.data[i];
  return result;
}

