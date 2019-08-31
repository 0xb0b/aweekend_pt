template<typename Typeclass, typename T>
struct Instance
{}

#define INSTANCE(Typeclass, T) template<> struct Instance<Typeclass, T> {using type = T;};

#define REQUIRE_INSTANCE(Typeclass, T) typename = Instance<Typeclass, T>::type

/* auxiliary type to express typeclass constraints (value metafunction)
template<typename Typeclass, typename T>
struct Instance
{
  static constexpr bool value = false;
}

   - define type X
   - specialize Instance for concrete typeclass (e.g. Eq) and X:
       template<>
       struct Instance<Eq, X>
       {
         static constexpr bool value = true;
       };
     may define macro for this:
#define INSTANCE(Typeclass, T) = template<> struct Instance<Typeclass, T> {static constexpr bool value = true;};

function to check typeclass constraints:
     requireInstance<Eq, X>();
   or define macro:
#define REQUIRE_INSTANCE(Typeclass, T) = static_assert(Instance<Typeclass, T>::value, "");

template<typename Typeclass, typename T>
constexpr void requireInstance()
{
  static_assert(Instance<Typeclass, T>::value, "");
}
*/

/*
open questions:
    - how to automatically generate interface functions for ADTs?
      like default operator== for a type that consists of Eq types
*/
