#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct Material {
  Material(const PixelRGB& diffuse_color, const Vec2& albedo,
           double specular_exp)
      : m_diffuse_color{diffuse_color},
        m_albedo{albedo},
        m_specular_exp{specular_exp} {}

  Material() : m_diffuse_color{}, m_albedo{1.0}, m_specular_exp{} {}

  PixelRGB m_diffuse_color{};
  Vec2 m_albedo{};
  double m_specular_exp{};
};

#endif
