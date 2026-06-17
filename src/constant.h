#ifndef CONSTANT_H
#define CONSTANT_H

#include <numbers>

#include "material.h"
#include "vector.h"

// clang-format off
namespace constant {
constexpr int width {1024};
constexpr int height{ 768};
}

namespace camera {
constexpr Coord3D origin{0.0, 0.0, 0.0};
constexpr double  fov   {std::numbers::pi / 2.0};
}

namespace color {
constexpr PixelRGB lightblue{0.2, 0.7, 0.8};
constexpr PixelRGB gray     {0.4, 0.4, 0.3};
}

namespace material {
const Material ivory     {Vec3{0.6,  0.3, 0.1}, PixelRGB{0.4, 0.4, 0.3},   50.0};
const Material red_rubber{Vec3{0.9,  0.1, 0.0}, PixelRGB{0.3, 0.1, 0.1},   10.0};
const Material mirror    {Vec3{0.0, 10.0, 0.8}, PixelRGB{1.0, 1.0, 1.0}, 1425.0};
}
// clang-format on

#endif
