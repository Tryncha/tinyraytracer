#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"

struct Light {
  Light(const Vec3& position, double intensity)
      : m_position{position}, m_intensity{intensity} {}

  Coord3D m_position{};
  double m_intensity{};
};

#endif
