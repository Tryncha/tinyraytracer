#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

#include "constant.h"
#include "light.h"
#include "material.h"
#include "sphere.h"
#include "vector.h"

Vec3 reflect(const Vec3& I, const Vec3& N) { return I - N * 2.0 * (I * N); }

bool scene_intersect(const Coord3D& origin, const Vec3& dir,
                     const std::vector<Sphere>& spheres, Coord3D& hit, Vec3& N,
                     Material& material) {
  double spheres_dist{std::numeric_limits<float>::max()};

  for (std::size_t i{0}; i < spheres.size(); ++i) {
    double dist_i{};

    if (spheres[i].is_intersect(origin, dir, dist_i) && dist_i < spheres_dist) {
      spheres_dist = dist_i;
      hit = origin + dir * dist_i;
      N = normalize(hit - spheres[i].m_center);
      material = spheres[i].m_material;
    }
  }

  return spheres_dist < 1000.0;
}

PixelRGB cast_ray(const Coord3D& origin, const Vec3& dir,
                  const std::vector<Sphere>& spheres,
                  const std::vector<Light>& lights) {
  Coord3D hit{};
  Vec3 N{};
  Material material{};

  if (!scene_intersect(origin, dir, spheres, hit, N, material)) {
    return color::lightblue;
  }

  double diffuse_light_intensity{};
  double specular_light_intensity{};

  for (std::size_t i{0}; i < lights.size(); ++i) {
    Vec3 light_dir{normalize(lights[i].m_position - hit)};

    diffuse_light_intensity +=
        lights[i].m_intensity * std::max(0.0, light_dir * N);
    specular_light_intensity +=
        std::pow(std::max(0.0, -1.0 * reflect(-1.0 * light_dir, N) * dir),
                 material.m_specular_exp) *
        lights[i].m_intensity;
  }

  return (material.m_diffuse_color * diffuse_light_intensity *
          material.m_albedo[0]) +
         (Vec3{1.0, 1.0, 1.0} * specular_light_intensity *
          material.m_albedo[1]);
}

void render(std::vector<PixelRGB>& framebuffer,
            const std::vector<Sphere>& spheres,
            const std::vector<Light>& lights) {
  for (int j{0}; j < constant::height; ++j) {
    for (int i{0}; i < constant::width; ++i) {
      const double x{(2 * (i + 0.5) / constant::width - 1) *
                     (tan(camera::fov / 2.0) * constant::width) /
                     constant::height};

      const double y{-(2 * (j + 0.5) / constant::height - 1) *
                     tan(camera::fov / 2.0)};

      const Vec3 dir{normalize(Vec3{x, y, -1})};

      framebuffer[static_cast<std::size_t>(i + (j * constant::width))] =
          cast_ray(camera::origin, dir, spheres, lights);
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

  for (auto pixel : framebuffer) {
    double max{std::max(pixel[0], std::max(pixel[1], pixel[2]))};
    if (max > 1.0) pixel = pixel * (1.0 / max);

    for (std::size_t channel{0}; channel < 3; ++channel) {
      const auto value{static_cast<std::uint8_t>(
          255.0 * std::clamp(pixel[channel], 0.0, 1.0))};

      ofs.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
  }
}

int main(int, char**) {
  std::vector<PixelRGB> framebuffer(constant::width * constant::height);

  std::vector<Sphere> spheres{};
  std::vector<Light> lights{};

  // clang-format off
  spheres.push_back(Sphere{Coord3D{{-3.0,  0.0, -16.0}}, 2, material::ivory});
  spheres.push_back(Sphere{Coord3D{{-1.0, -1.5, -12.0}}, 2, material::red_rubber});
  spheres.push_back(Sphere{Coord3D{{ 1.5, -0.5, -18.0}}, 3, material::red_rubber});
  spheres.push_back(Sphere{Coord3D{{ 7.0,  5.0, -18.0}}, 4, material::ivory});

  lights.push_back(Light{Coord3D{{-20.0, 20.0,  20.0}}, 1.5});
  lights.push_back(Light{Coord3D{{ 30.0, 50.0, -25.0}}, 1.8});
  lights.push_back(Light{Coord3D{{ 30.0, 20.0,  30.0}}, 1.7});
  // clang-format on

  render(framebuffer, spheres, lights);
  generate_ppm(framebuffer, "./gen_image.ppm");

  return 0;
}
