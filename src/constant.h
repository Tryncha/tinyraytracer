#ifndef CONSTANT_H
#define CONSTANT_H

#include <numbers>

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
// clang-format on

#endif
