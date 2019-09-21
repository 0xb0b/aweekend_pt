#pragma once

#include <utility>

// maybe just nothing

template<typename T>
struct Maybe
{
private:
  bool initialized;
  T value;

  // T has to be default constructible
  Maybe()
    : initialized {false}
  {}

  // TODO add other constructors?
  Maybe(T&& v)
    : initialized {true}
    , value {v}
  {}

  // TODO add copy constructor and assignment operator

  // fromMaybe :: a -> Maybe a -> a
};

template<typename T>
T fromMaybe(T defaultValue, Maybe<T> something)
{
  if (something.initialized)
    return something.value;
  else
    return defaultValue;
}


/* examples:

Maybe<int> foo(int x)
{
  if (x < 0)
    return;
  else
    return x;
}

Maybe<int> a {};
a = foo(3);
int y = fromMaybe(0, a);

*/

