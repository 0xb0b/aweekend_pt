#pragma once

// !!!
// similar data with different behavior - template type with tags
// different data with similar behavior - typeclass

class Typeclass
{
  Typeclass() = delete;
};

/* typeclass defined as a template

template<typename T>
class Nameit final : Typeclass
{};

then there is a concrete type Nameit<A> that corresponds to a type A instance of the
typeclass Nameit;
this Nameit<A> type is not used directly, so why not make a typeclass just a tag type,
and not a template?
the typeclass definition has to have a type in it. without having type in a typeclass
definition on can not for example have the additional constraints on type in typeclasses:

template<typename T, REQUIRE_INSTANCE(Eq, T)>
class Ord ...

compare with Haskell typeclass definition:

class Eq a where
...

or typeclass with an additional constraint:

class Eq a => Ord a where
...
*/

// Instance is the compile time function over types which is false (0) except when it is
// true (1) for the types which are instances of a typeclass
template<typename T>
struct Instance
{
  static constexpr bool value = false;
};

// does not work if type a itself is a template
// because of comma in macro argument
// and because in this case template header has to be nonempty
#define INSTANCE(typeclass, a) template<> \
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

