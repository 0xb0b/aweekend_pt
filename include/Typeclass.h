#pragma once

// !!!
// similar data implementation with different behavior - template type with tags
// different data implementation with similar behavior - typeclass

/* template<typename Typeclass, typename T> */
// struct Instance
// {};
// 
// #define INSTANCE(Typeclass, T) template<> struct Instance<Typeclass, T> {using type = T;};
// 
/* #define REQUIRE_INSTANCE(Typeclass, T) typename = typename Instance<Typeclass, T>::type */

class Typeclass
{
  Typeclass() = delete;
};

// Instance is the compile time function over types which is false (0) except when it is
// true (1) for the types which are instances of a typeclass
template<typename T>
struct Instance
{
  static constexpr bool value = false;
};

#define INSTANCE(typeclass, a) template<> \
struct Instance<typeclass<a>> {static constexpr bool value = true;};

#define INSTANCE_TEMPLATE(typeclass, a, template_decl) template \
struct Instance<typeclass<a>> {static constexpr bool value = true;};

template<typename T>
struct Require
{
  static_assert(Instance<T>::value, "typeclass instance required ");
  using type = void;
};

#define REQUIRE_INSTANCE(typeclass, a) typename = typename Require<typeclass<a>>::type

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

