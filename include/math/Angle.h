#pragma once


extern const float pi;


struct Degree
{
  float value;

  Degree (float a)
    : value {a}
  {}

  Degree (const Degree& other)
    :value {other.value}
  {}
};

struct Radian
{
  float value;

  Radian (float a)
    : value {a}
  {}

  Radian (const Radian& other)
    :value {other.value}
  {}
};

Radian toRadian(Degree);

Degree toDegree(Radian);

