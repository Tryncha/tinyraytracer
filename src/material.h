#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

struct Material {
  PixelRGB m_diffuse_color{};

  Material(const PixelRGB& diffuse_color) : m_diffuse_color(diffuse_color) {}
  Material() : m_diffuse_color() {}
};

#endif
