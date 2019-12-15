#include <math/Angle.h>


namespace internal
{
constexpr float pi = 3.14159265358979323846;
}

// TODO why constexpr + const?
const float pi = internal::pi;


Radian toRadian(Degree angle)
{
  static constexpr float k = internal::pi / 180;
  return angle.value * k;
}

Degree toDegree(Radian angle)
{
  static constexpr float k = 180 / internal::pi;
  return angle.value * k;
}

