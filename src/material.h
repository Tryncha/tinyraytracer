#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct Material {
  Material(const Vec3& albedo, const PixelRGB& diffuse_color,
           double specular_exp)
      : m_albedo{albedo},
        m_diffuse_color{diffuse_color},
        m_specular_exp{specular_exp} {}

  Material() : m_albedo{1, 0, 0}, m_diffuse_color{}, m_specular_exp{} {}

  Vec3 m_albedo{};
  PixelRGB m_diffuse_color{};
  double m_specular_exp{};
};

#endif
