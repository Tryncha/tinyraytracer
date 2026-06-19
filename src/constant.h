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
const Material ivory {Vec4{0.6,  0.3, 0.1, 0.0}, PixelRGB{0.4, 0.4, 0.3},
                        50.0, 1.0};
const Material rubber{Vec4{0.9,  0.1, 0.0, 0.0}, PixelRGB{0.3, 0.1, 0.1},
                        10.0, 1.0};
const Material mirror{Vec4{0.0, 10.0, 0.8, 0.0}, PixelRGB{1.0, 1.0, 1.0},
                      1425.0, 1.0};
const Material glass {Vec4{0.0,  0.5, 0.1, 0.8}, PixelRGB{0.6, 0.7, 0.8},
                       125.0, 1.5};
}
// clang-format on

#endif
