#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

#include <Camera.h>
#include <Maybe.h>
#include <light/Color.h>
#include <light/Ray.h>


struct Sphere
{
  float radius;
  Point3f center;

  explicit Sphere(float r)
    : radius {r}
    , center {zero<Point3f>}
  {}

  Sphere(float r, Point3f p)
    : radius {r}
    , center {p}
  {}
};

using ObjList = std::vector<Sphere>;



struct Intersection
{
  float parameter;
  Point3f point;
  Vector3f normal;

  Intersection()
    : point {zero<Point3f>}
    , normal {zero<Vector3f>}
  {}

  Intersection(float t, Point3f p, Vector3f n)
    : parameter {t}
    , point {p}
    , normal {n}
  {}
};


Maybe<Intersection> intersect(const Ray& r, const Sphere& obj)
{
  const auto centerToRayOrigin {toVector(r.origin - obj.center)};
  const auto a = dot(r.direction, r.direction);
  const auto b = dot(centerToRayOrigin, r.direction);
  const auto c = dot(centerToRayOrigin, centerToRayOrigin) - obj.radius * obj.radius;
  const auto discriminant = b * b - a * c;
  if (discriminant > 0.0f)
  {
    // return closest point
    const float t = (- b - sqrt(discriminant)) / a;
    if (t > 0.0f)
    {
      const auto intersectionPoint {translate(r.origin, scale(r.direction, t))};
      auto normal {toVector(intersectionPoint - obj.center)};
      normalize_m(normal);
      return Intersection(t, intersectionPoint, normal);
    }
  }
  return {};
}

Maybe<Intersection> intersect(const Ray& r, const ObjList& scene)
{
  float closest_t = std::numeric_limits<float>::max();
  Maybe<Intersection> x;
  for (size_t i = 0; i < scene.size(); i++)
  {
    const auto& object = scene.at(i);
    const auto maybeIntersection = intersect(r, object);
    if (maybeIntersection && maybeIntersection.value.parameter < closest_t)
    {
      x = maybeIntersection;
      closest_t = x.value.parameter;
    }
  }
  return x;
}

Color3 colorize(const Ray& r, const ObjList& scene)
{
  // background
  const auto kup = 0.5f * (1.0f + z(r.direction));
  const auto white = unit<Color3>;
  const auto blue = Color3(0.1f, 0.2f, 0.8f);
  const auto red = Color3(0.8f, 0.2f, 0.1f);
  auto color = mix(white, blue, kup);

  const auto maybeIntersection = intersect(r, scene);
  if (maybeIntersection)
  {
    auto n {maybeIntersection.value.normal};
    n += unit<Vector3f>;
    scale_m(n, 0.5f);
    color = Color3(x(n), y(n), z(n));
  }

  return color;
}


int main()
{
  int hresolution = 512;
  int vresolution = 288;
  const Camera cam {zero<Point3f>, Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f),
                    hresolution, vresolution, Degree(90.0f)};

  const ObjList scene {{0.5f, Point3f(-2.0f, 0.0f, 0.0f)},
                       {100.0f, Point3f(-2.0f, 0.0f, -101.0f)}};

  std::cout << "#dbg " << cam;
  std::ofstream outstream;
  outstream.open("render.ppm");
  outstream << "P3\n" << hresolution << " " << vresolution << "\n255\n";
  size_t samplesNum = 16;
  for (int j = 0; j < vresolution; j++)
  {
    for (int i = 0; i < hresolution; i++)
    {
      auto color {zero<Color3>};
      for (size_t s = 0; s < samplesNum; s++)
      {
        const auto ray {generateRay(cam, i, j)};
        // made the cool color arithmetic. how to accumulate now bleat?!
        color += colorize(ray, scene);
      }
      // how to average suka?!
      scale_m(color, 1.0f / samplesNum);
      const Rgb sdcolor {color};
      outstream << static_cast<int>(sdcolor.r) << " " << static_cast<int>(sdcolor.g) << " "
                << static_cast<int>(sdcolor.b) << "\n";
    }
  }
  outstream.close();
  return 0;
}

