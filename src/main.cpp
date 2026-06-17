#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "constant.h"
#include "vector.h"

void generate_ppm(const std::string& filename) {
  using Pixel = Vector<float, 3>;
  std::vector<Pixel> framebuffer(constant::width * constant::height);

  for (std::size_t y{0}; y < constant::height; ++y) {
    for (std::size_t x{0}; x < constant::width; ++x) {
      framebuffer[x + (y * constant::width)] = Pixel{
          static_cast<float>(y) / static_cast<float>(constant::height),
          static_cast<float>(x) / static_cast<float>(constant::width), 0.0f};
    }
  }

  // Save the framebuffer to file
  std::ofstream ofs(filename, std::ios::binary);

  if (!ofs) {
    throw std::runtime_error("Failed to open output file");
  }

  ofs << "P6\n" << constant::width << ' ' << constant::height << "\n255\n";

  for (const auto& pixel : framebuffer) {
    for (std::size_t channel{0}; channel < 3; ++channel) {
      const auto value{static_cast<std::uint8_t>(
          255.0f * std::clamp(pixel[channel], 0.0f, 1.0f))};

      ofs.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
  }
}

int main(int, char**) {
  generate_ppm("./gen_image.ppm");
  return 0;
}
