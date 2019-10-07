#include <cmath>
#include <iostream>
#include <random>
#include <utility>

#include <Camera.h>


namespace
{

std::pair<float, float> stdrandom()
{
  static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
  static std::mt19937 generator;
  static bool initialized = false;
  if (!initialized)
  {
    generator.seed(42);
    initialized = true;
  }
  return {distribution(generator), distribution(generator)};
}

std::pair<float, float> quasirandom()
{
  // http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/
  static const float seed = 0.5f;
  static const float g = 1.32471795724474602596;
  static const float a = 1.0f / g;
  static const float b = a / g;
  static float na = seed;
  static float nb = seed;
  na += a;
  nb += b;
  float _;
  float x = modff(na, &_);
  float y = modff(nb, &_);
  return {x, y};
}

}

// https://pacoup.com/2011/06/12/list-of-true-169-resolutions/
// some good 16:9 resolutions:
// 64 x 36
// 128 x 72
// 256 x 144
// 384 x 216
// 512 x 288
// 1024 x 576
// 1280 x 720  720p HD
// 1920 x 1080 1080p HD
// 2560 x 1440
const int default_xresolution = 512;
const int default_yresolution = 288;


Camera::Camera()
  : xresolution {default_xresolution}
  , yresolution {default_yresolution}
  , flength { static_cast<float>(yresolution) }
  , position {0.0f, 0.0f, 10.0f}
  , look {0.0f, 0.0f, -flength} // down the world z axis
  , up {0.0f, 1.0f, 0.0f}
  , right {1.0f, 0.0f, 0.0f}
{}

Camera::Camera(Point3f pos, Vector3f lookVec, Vector3f upVec, int xres, int yres,
               Degree yfov) : Camera()
{
  xresolution = xres;
  yresolution = yres;

  flength = static_cast<float>(yresolution) / std::tan(toRadian(yfov).value / 2);

  position = pos;

  look = normalize_m(lookVec);
  scale_m(look, flength);

  // make up direction to be perpendicular to look direction:
  //   subtract projection of the up vector on the look vector
  up = upVec - scale_m(lookVec, dot(upVec, lookVec));
  if (up == zero<Vector3f>)
  {
    // degenerate case, up vector is collinear with look vector
    // make up vector to be some vector in a plane for which look is normal
    if (std::abs(x(look)) >= std::abs(y(look)))
    {
      up = Vector3f(z(look), 0, -x(look));
    }
    else
    {
      up = Vector3f(0, z(look), -y(look));
    }
  }
  normalize_m(up);

  right = cross(look, up);
  normalize_m(right);
}

Camera::Camera(Point3f pos, Point3f lookAtPoint, Vector3f upVec, int xres, int yres,
               Degree yfov) : Camera(pos, toVector(lookAtPoint - pos), upVec, xres, yres, yfov)
{}


Ray generateRay(const Camera& cam, int i, int j)
{
  // steer direction to the random point inside the screen pixel
  // const auto sample = quasirandom();
  const auto sample = stdrandom();
  auto x = static_cast<float>(i) - cam.xresolution / 2.0f + sample.first;
  auto y = cam.yresolution / 2.0f - static_cast<float>(j) - sample.second;
  auto direction {cam.look};
  direction += scale(cam.up, y);
  direction += scale(cam.right, x);
  return {cam.position, direction};
}

std::ostream& operator<<(std::ostream& out, const Camera& cam)
{
  out << "Camera\n  resolution: (" << cam.xresolution << "x" << cam.yresolution << ")\n"
      << "  focal length: " << cam.flength << "\n"
      << "  position: (" << x(cam.position) << ", "
                         << y(cam.position) << ", "
                         << z(cam.position) << ")\n"
      << "  look: (" << x(cam.look) << ", " << y(cam.look) << ", " << z(cam.look) << ")\n"
      << "  up: (" << x(cam.up) << ", " << y(cam.up) << ", " << z(cam.up) << ")\n"
      << "  right: (" << x(cam.right) << ", " << y(cam.right) << ", " << z(cam.right) << ")\n";
  return out;
}

