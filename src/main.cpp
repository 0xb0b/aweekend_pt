#include <iostream>
#include <fstream>
#include <limits>
#include <random>
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


// TODO make sampling module
float stdrandom(float minVal = 0.0f, float maxVal = 1.0f)
{
  static std::uniform_real_distribution<float> distribution(minVal, maxVal);
  static std::mt19937 generator;
  static bool initialized = false;
  if (!initialized)
  {
    generator.seed(42);
    initialized = true;
  }
  return distribution(generator);
}

Vector3f randomInUnitSphereByRej()
{
  Vector3f a {stdrandom(-1.0f, 1.0f), stdrandom(-1.0f, 1.0f), stdrandom(-1.0f, 1.0f)};
  while (dot(a, a) > 1.0f)
    a = Vector3f(stdrandom(), stdrandom(), stdrandom());
  return a;
}

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
      auto intersectionPoint {translate(r.origin, scale(r.direction, t))};
      auto normal {toVector(intersectionPoint - obj.center)};
      normalize_m(normal);
      // move intersection point slightly so it is not inside the sphere due to numerical error
      // translate_m(intersectionPoint, scale(normal, 0.001f));
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
  static const auto white = unit<Color3>;
  static const auto blue = Color3(0.1f, 0.2f, 0.8f);
  static const auto red = Color3(0.8f, 0.2f, 0.1f);
  static float attenuation = 0.5f;

  const auto maybeIntersection = intersect(r, scene);
  if (maybeIntersection)
  {
    const auto& n = maybeIntersection.value.normal;
    const auto& p = maybeIntersection.value.point;
    auto scatterDir {n};
    scatterDir += randomInUnitSphereByRej();
    // infinite recursion!
    return scale(colorize(Ray(p, scatterDir), scene), attenuation);
  }
  else
  {
    // background
    const auto kup = 0.5f * (1.0f + z(r.direction));
    return mix(white, blue, kup);
  }
}

Color3 gammaCorrect(const Color3& color)
{
  return {std::sqrt(r(color)), std::sqrt(g(color)), std::sqrt(b(color))};
}


int main()
{
  int hresolution = 512;
  int vresolution = 288;
  const Camera cam {zero<Point3f>, Vector3f(-1.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f),
                    hresolution, vresolution, Degree(90.0f)};

  const ObjList scene {{0.5f, Point3f(-2.0f, 0.0f, 0.0f)},
                       {100.0f, Point3f(-2.0f, 0.0f, -100.51f)}};

  std::cout << "#dbg " << cam;
  std::ofstream outstream;
  outstream.open("render.ppm");
  outstream << "P3\n" << hresolution << " " << vresolution << "\n255\n";
  size_t spp = 128;
  for (int j = 0; j < vresolution; j++)
  {
    for (int i = 0; i < hresolution; i++)
    {
      auto color {zero<Color3>};
      for (size_t s = 0; s < spp; s++)
      {
        const auto ray {generateRay(cam, i, j)};
        color += colorize(ray, scene);
      }
      scale_m(color, 1.0f / spp);
      const Rgb sdcolor {gammaCorrect(color)};
      outstream << static_cast<int>(sdcolor.r) << " " << static_cast<int>(sdcolor.g) << " "
                << static_cast<int>(sdcolor.b) << "\n";
    }
  }
  outstream.close();
  return 0;
}

