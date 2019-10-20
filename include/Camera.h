#pragma once

#include<light/Ray.h>
#include<math/Angle.h>


extern const int default_xresolution;
extern const int default_yresolution;


// thin lens approximation camera model
struct Camera
{
  int xresolution;
  int yresolution;
  float flength;
  float pixelSize;
  float apertureRadius;
  // position and orientation assumed to be in the world coordinate system
  // this is not how the camera is made usually, but let it be until I know more about camera
  // matrix and transformations
  Point3f position;
  Vector3f look;
  Vector3f up;
  Vector3f right;

  Camera();

  Camera(Point3f pos, Vector3f lookVec, Vector3f upVec,
         int xres = default_xresolution, int yres = default_yresolution,
         Degree yfov = Degree(90.0f), float f = 1.0f, float aperture = 0.0f);

  Camera(Point3f pos, Point3f lookAtPoint, Vector3f upVec,
         int xres = default_xresolution, int yres = default_yresolution,
         Degree yfov = Degree(90.0f), float f = 1.0f, float aperture = 0.0f);
};

// TODO make Show typeclass?
std::ostream& operator<<(std::ostream&, const Camera&);

Ray generateRay(const Camera&, int, int);

