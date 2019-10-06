#include <iostream>
#include <fstream>
#include <Camera.h>
#include <light/Color.h>
#include <light/Ray.h>


Rgb colorize(const Ray& r)
{
  const auto kup = 0.5f * (1.0f + z(r.direction));
  const auto kright = 0.5f * (1.0f + x(r.direction));
  const auto white = unit<Color3>;
  const auto blue = Color3(Channelf(0.1f), Channelf(0.2f), Channelf(0.8f));
  const auto red = Color3(Channelf(0.8f), Channelf(0.2f), Channelf(0.1f));
  // auto color = mix(white, blue, Channelf(kup));
  const auto rayDirection = normalize(r.direction);
  Color3 color {Channelf(x(rayDirection)), Channelf(y(rayDirection)), Channelf(z(rayDirection))};
  // color += Color3(Channelf(0.2f));
  //color = mix(color, red, Channelf(kright));
  return Rgb(color);
}

int main()
{
  int hresolution = 512;
  int vresolution = 288;
  const Camera cam {zero<Point3f>, Vector3f(1.0f, 1.0f, 1.0f), Vector3f(0.0f, 0.0f, 1.0f),
                    hresolution, vresolution, Degree(90.0f)};
  std::cout << "#dbg " << cam;
  std::ofstream outstream;
  outstream.open("render.ppm");
  outstream << "P3\n" << hresolution << " " << vresolution << "\n255\n";
  for (int j = 0; j < vresolution; j++)
  {
    for (int i = 0; i < hresolution; i++)
    {
      const auto ray {generateRay(cam, i, j)};
      const auto color {colorize(ray)};
      outstream << static_cast<int>(color.r) << " " << static_cast<int>(color.g) << " "
                << static_cast<int>(color.b) << "\n";
    }
  }
  outstream.close();
  return 0;
}

