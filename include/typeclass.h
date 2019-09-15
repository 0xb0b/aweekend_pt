#pragma once

/* template<typename Typeclass, typename T> */
// struct Instance
// {};
// 
// #define INSTANCE(Typeclass, T) template<> struct Instance<Typeclass, T> {using type = T;};
// 
/* #define REQUIRE_INSTANCE(Typeclass, T) typename = typename Instance<Typeclass, T>::type */

template<typename Typeclass, typename T>
struct Instance
{
  static constexpr bool value = false;
};

#define MAKE_INSTANCE(Typeclass, T) template<> \
struct Instance<Typeclass, T> {static constexpr bool value = true;};

template<typename Typeclass, typename T>
struct Require
{
  using type = void;
  static_assert(Instance<Typeclass, T>::value, "type has to be instance of typeclass");
};

#define REQUIRE_INSTANCE(Typeclass, T) typename = typename Require<Typeclass, T>::type

/* using require = int; */
// 
// template<typename Typeclass, typename T>
// constexpr require instance()
// {
  // static_assert(Instance<Typeclass, T>::value, "type has to be instance of typeclass");
  // return 0;
/* } */

/*
open questions:
    - how to automatically generate interface functions for ADTs?
      like default operator== for a type that consists of Eq types
*/

