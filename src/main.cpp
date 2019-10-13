#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <vector>

#include <Camera.h>
#include <Maybe.h>
#include <light/Color.h>
#include <light/Ray.h>


const int maxDepth = 4;


// TODO make sampling module
float stdrandom(float minVal = 0.0f, float maxVal = 1.0f)
{
  static std::uniform_real_distribution<float> sampleDistribution(minVal, maxVal);
  static std::mt19937 generator;
  static bool initialized = false;
  if (!initialized)
  {
    generator.seed(42);
    initialized = true;
  }
  return sampleDistribution(generator);
}

Vector3f randomInUnitSphereByRej()
{
  Vector3f a {stdrandom(-1.0f, 1.0f), stdrandom(-1.0f, 1.0f), stdrandom(-1.0f, 1.0f)};
  while (dot(a, a) > 1.0f)
    a = Vector3f(stdrandom(), stdrandom(), stdrandom());
  return a;
}


struct ScatterInfo
{
  Color3 albedo;
  Vector3f direction;

  ScatterInfo(Color3 a, Vector3f d)
    : albedo {a}
    , direction {d}
  {}
};

// Material<Lambertian>(diffuseMaterials[0]);

struct Material
{
  // Maybe<HitInfo> requires default constructible through HitInfo::material
  Material() = default;

  template<typename T>
  explicit Material(const T& m)
    : handle {&m}
    , dispatch {&invoke<T>}
  {}

  template<typename T>
  static ScatterInfo invoke(const void* handle, const Vector3f& incident, const Vector3f& normal)
  {
    const auto& m = *(static_cast<const T*>(handle));
    return scatter(incident, normal, m);
  }

  // type is erased!
  const void* handle;
  ScatterInfo (*dispatch)(const void*, const Vector3f&, const Vector3f&);
};

struct Lambertian
{
  Color3 albedo;

  explicit Lambertian(Color3 a)
    : albedo {a}
  {}
};

struct Metallic
{
  Color3 albedo;

  explicit Metallic(Color3 a)
    : albedo {a}
  {}
};

struct HitInfo
{
  float parameter;
  Point3f point;
  Vector3f normal;
  Material material;

  // Maybe<HitInfo> requires default constructible
  HitInfo()
    : point {zero<Point3f>}
    , normal {zero<Vector3f>}
  {}

  HitInfo(float t, Point3f p, Vector3f n, Material m)
    : parameter {t}
    , point {p}
    , normal {n}
    , material {std::move(m)}
  {}
};

struct Procedural
{
  template<typename T>
  explicit Procedural(const T& obj)
    : handle {&obj}
    , dispatch {&invoke<T>}
  {}

  template<typename T>
  static Maybe<HitInfo> invoke(const void* handle, const Ray& r)
  {
    const auto& obj = *(static_cast<const T*>(handle));
    return intersect(r, obj);
  }

  // type is erased!
  const void* handle;
  Maybe<HitInfo> (*dispatch)(const void*, const Ray&);
};

using ObjList = std::vector<Procedural>;

struct Sphere
{
  float radius;
  Point3f center;
  Material material;

  explicit Sphere(float r, Material m)
    : radius {r}
    , center {zero<Point3f>}
    , material {std::move(m)}
  {}

  Sphere(float r, Point3f p, Material m)
    : radius {r}
    , center {p}
    , material {std::move(m)}
  {}
};


Maybe<HitInfo> intersect(const Ray& r, const Procedural& obj)
{
  return (*obj.dispatch)(obj.handle, r);
}

Maybe<HitInfo> intersect(const Ray& r, const Sphere& obj)
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
      auto hitPoint {translate(r.origin, scale(r.direction, t))};
      auto normal {toVector(hitPoint - obj.center)};
      scale_m(normal, 1.0f / obj.radius);
      // move intersection point slightly so it is not inside the sphere due to numerical error
      // translate_m(intersectionPoint, scale(normal, 0.001f));
      return HitInfo(t, hitPoint, normal, obj.material);
    }
  }
  return {};
}

ScatterInfo scatter(const Vector3f incident, const Vector3f normal, const Material& m)
{
  return (*m.dispatch)(m.handle, incident, normal);
}

ScatterInfo scatter(const Vector3f incident, const Vector3f normal, const Lambertian& m)
{
  auto nextRayDir {normal};
  // TODO what happens if this is (approximately)zero vector?
  nextRayDir += randomInUnitSphereByRej();
  return {m.albedo, nextRayDir};
}

ScatterInfo scatter(const Vector3f incident, const Vector3f normal, const Metallic& m)
{
  auto nextRayDir {incident};
  nextRayDir -= scale(normal, 2 * dot(incident, normal));
  return {m.albedo, nextRayDir};
}

Maybe<HitInfo> intersect(const Ray& r, const ObjList& world)
{
  float closest_t = std::numeric_limits<float>::max();
  Maybe<HitInfo> x;
  for (size_t i = 0; i < world.size(); i++)
  {
    const auto& object = world.at(i);
    const auto maybeHit = intersect(r, object);
    if (maybeHit && maybeHit.value.parameter < closest_t)
    {
      x = maybeHit;
      closest_t = x.value.parameter;
    }
  }
  return x;
}

Color3 trace(const Ray& r, const ObjList& world, int depth=0)
{
  static const auto white = unit<Color3>;
  static const auto blue = Color3(0.1f, 0.2f, 0.8f);
  static const auto red = Color3(0.8f, 0.2f, 0.1f);

  if (depth == maxDepth)
    return zero<Color3>;

  const auto maybeHit = intersect(r, world);
  if (maybeHit)
  {
    const auto& hit = maybeHit.value;
    const auto interaction {scatter(r.direction, hit.normal, hit.material)};
    // infinite recursion!
    const Ray nextRay {hit.point, interaction.direction};
    auto incoming {trace(nextRay, world, ++depth)};
    return incoming * interaction.albedo;
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

  const std::vector<Lambertian> diffuseMaterials { Lambertian(Color3(0.7f, 0.3f, 0.3f)),
                                                   Lambertian(Color3(0.3f, 0.3f, 0.3f)) };
  const std::vector<Metallic> metalMaterials { Metallic(Color3(0.8f, 0.6f, 0.2f)),
                                               Metallic(Color3(0.8f, 0.8f, 0.8f)) };

  const std::vector<Sphere> spheres {
    {0.5f, Point3f(-2.0f, 0.0f, 0.0f), Material(diffuseMaterials[0])},
    {100.0f, Point3f(-2.0f, 0.0f, -100.5f), Material(diffuseMaterials[1])},
    {0.8f, Point3f(-2.0f, 1.3f, 0.3f), Material(metalMaterials[0])},
    {0.4f, Point3f(-2.0f, -0.9f, -0.1f), Material(metalMaterials[1])}
  };

  const ObjList world { Procedural(spheres[0]), Procedural(spheres[1]),
    Procedural(spheres[2]), Procedural(spheres[3]) };

  std::cout << "#dbg " << cam;
  std::ofstream outstream;
  outstream.open("render.ppm");
  outstream << "P3\n" << hresolution << " " << vresolution << "\n255\n";
  size_t spp = 16;
  float reciprocalSpp = 1.0f / spp;
  for (int j = 0; j < vresolution; j++)
  {
    for (int i = 0; i < hresolution; i++)
    {
      auto color {zero<Color3>};
      for (size_t s = 0; s < spp; s++)
      {
        const auto ray {generateRay(cam, i, j)};
        color += trace(ray, world);
      }
      scale_m(color, reciprocalSpp);
      const Rgb sdcolor {gammaCorrect(color)};
      outstream << static_cast<int>(sdcolor.r) << " " << static_cast<int>(sdcolor.g) << " "
                << static_cast<int>(sdcolor.b) << "\n";
    }
  }
  outstream.close();
  return 0;
}

