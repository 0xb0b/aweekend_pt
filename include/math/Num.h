#pragma once

using Float = float;

template<typename T>
struct Zero
{
  static constexpr T value = static_cast<T>(0);
}

template<typename T>
struct Unit
{
  static constexpr T value = static_cast<T>(1);
}

