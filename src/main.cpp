#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "constant.h"
#include "vector.h"

class Sphere {
 private:
  Coord3D m_center{};
  double m_radius{};

 public:
  Sphere(const Coord3D& center, double radius)
      : m_center{center}, m_radius{radius} {}

  std::optional<double> intersect(const Coord3D& origin,
                                  const Vec3& dir_norm) const {
    // Vector from origin to center
    const Vec3 L{m_center - origin};
    // t closest approach
    const double tca{L * dir_norm};
    // Distance squared
    const double dist_sq{L * L - tca * tca};

    if (dist_sq > m_radius * m_radius) {
      return std::nullopt;
    }

    // t half chord
    const double thc{std::sqrt((m_radius * m_radius) - dist_sq)};
    // t_min and t_max are solutions for the equation
    double t_min{tca - thc};
    double t_max{tca + thc};

    if (t_min < 0) {
      t_min = t_max;
    }

    if (t_min < 0) {
      return std::nullopt;
    }

    return t_min;
  }
};

PixelRGB cast_ray(const Coord3D& orig, const Vec3& dir, const Sphere& sphere) {
  auto hit{sphere.intersect(orig, dir)};

  if (!hit) {
    // double sphere_dist{*hit};
    return color::lightblue;
  }

  return color::gray;
}

void render(std::vector<PixelRGB>& framebuffer, const Sphere& sphere) {
  for (int j{0}; j < constant::height; ++j) {
    for (int i{0}; i < constant::width; ++i) {
      const double x{(2 * (i + 0.5) / constant::width - 1) *
                     (tan(camera::fov / 2.0) * constant::width) /
                     constant::height};

      const double y{-(2 * (j + 0.5) / constant::height - 1) *
                     tan(camera::fov / 2.0)};

      const Vec3 dir{normalize(Vec3{x, y, -1})};

      framebuffer[static_cast<std::size_t>(i + (j * constant::width))] =
          cast_ray(camera::origin, dir, sphere);
    }
  }
}

void generate_ppm(const std::vector<PixelRGB>& framebuffer,
                  const std::string& filename) {
  // Save the framebuffer to file
  std::ofstream ofs(filename, std::ios::binary);

  if (!ofs) {
    throw std::runtime_error("Failed to open output file");
  }

  ofs << "P6\n" << constant::width << ' ' << constant::height << "\n255\n";

  for (const auto& pixel : framebuffer) {
    for (std::size_t channel{0}; channel < 3; ++channel) {
      const auto value{static_cast<std::uint8_t>(
          255.0 * std::clamp(pixel[channel], 0.0, 1.0))};

      ofs.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
  }
}

int main(int, char**) {
  std::vector<PixelRGB> framebuffer(constant::width * constant::height);

  const Sphere sphere{Coord3D{{-3.0, 0.0, -16.0}}, 2};

  render(framebuffer, sphere);
  generate_ppm(framebuffer, "./gen_image.ppm");

  return 0;
}
