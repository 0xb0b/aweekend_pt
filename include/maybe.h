// maybe just nothing

namespace core
{

// T has to be default constructible
template<typename T>
struct Maybe
{
private:
  bool isNothing;
  T value;

  // Just :: a -> Maybe a
  friend Maybe<T> Just(T&& value)
  {
    return {false, std::forward<T>(value)};
  }

  /* difference with haskell:

       Prelude> :t Just
       Just :: a -> Maybe a
       Prelude> :t Nothing
       Nothing :: Maybe a

       Nothing in haskell is a value with polymorphic type and not function
       type like Just;
       this can not be represented literally in c++
       so Nothing is represented as a function with no arguments returning
       polymorphic type */
  friend Maybe<T> Nothing()
  {
    return {true, T()};
  }

  // fromMaybe :: a -> Maybe a -> a
  friend T fromMaybe(T defaultValue, Maybe<T> something)
  {
    if (something.isNothing)
      return defaultValue;
    else
      return something.value;
  }
};

} // namespace core


/* examples:

Maybe<int> foo(int x)
{
  if (x < 0)
    return Nothing<int>();
  else
    return Just(x);
}


// define nothing for the type to avoid construction on each usage
constexpr auto nothingInt Nothing<int>();

Maybe<int> foo(int x)
{
  if (x < 0)
    return nothingInt;
  else
    return Just(x);
}

*/

