#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct Material {
  Material(const Vec4& albedo, const PixelRGB& diffuse_color,
           double specular_exp, double refractive_index)
      : m_albedo{albedo},
        m_diffuse_color{diffuse_color},
        m_specular_exp{specular_exp},
        m_refractive_index{refractive_index} {}

  Material()
      : m_albedo{1.0, 0.0, 0.0, 0.0},
        m_diffuse_color{},
        m_specular_exp{},
        m_refractive_index{1.0} {}

  Vec4 m_albedo{};
  PixelRGB m_diffuse_color{};
  double m_specular_exp{};
  double m_refractive_index{};
};

#endif
