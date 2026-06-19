#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"
#include "vector.h"

struct Sphere {
  Sphere(const Coord3D& center, const Material& material, double radius)
      : m_center{center}, m_material{material}, m_radius{radius} {}

  bool is_ray_intersect(const Coord3D& origin, const Vec3& dir_norm,
                        double& t_min) const {
    // Vector from origin to center
    const Vec3 L{m_center - origin};
    // t closest approach
    const double tca{L * dir_norm};
    // Distance squared
    const double dist_sq{L * L - tca * tca};

    if (dist_sq > m_radius * m_radius) {
      return false;
    }

    // t half chord
    const double thc{std::sqrt((m_radius * m_radius) - dist_sq)};
    // t_min and t_max are solutions for the equation
    t_min = tca - thc;
    double t_max{tca + thc};

    if (t_min < 0) {
      t_min = t_max;
    }

    if (t_min < 0) {
      return false;
    }

    return true;
  }

  Coord3D m_center{};
  Material m_material{};
  double m_radius{};
};

#endif
