#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

// Vector (mathematics and physics) implementation
template <typename T, std::size_t N>
struct Vector {
  std::array<T, N> values{};

  T& operator[](std::size_t i) {
    assert(i < N);
    return values[i];
  }

  const T& operator[](std::size_t i) const {
    assert(i < N);
    return values[i];
  }
};

// clang-format off
struct Coord3D  : Vector<double, 3> {};
struct Vec3     : Vector<double, 3> {};
struct PixelRGB : Vector<double, 3> {};
// clang-format on

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& v) {
  std::cout << '[';

  for (std::size_t i{0}; i < N; ++i) {
    if (i != 0) out << ", ";
    out << v[i];
  }

  std::cout << ']';

  return out;
}

// Addition
template <typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& lhv, const Vector<T, N>& rhv) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhv[i] + rhv[i];
  }

  return result;
}

// Substraction
template <typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& lhv, const Vector<T, N>& rhv) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhv[i] - rhv[i];
  }

  return result;
}

// Left scalar multiplication
template <typename T, std::size_t N>
Vector<T, N> operator*(T lhd, const Vector<T, N>& rhv) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhd * rhv[i];
  }

  return result;
}

// Right scalar multiplication
template <typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& lhv, T rhd) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhv[i] * rhd;
  }

  return result;
}

// Left scalar division
template <typename T, std::size_t N>
Vector<T, N> operator/(T lhd, const Vector<T, N>& rhv) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhd / rhv[i];
  }

  return result;
}

// Right scalar division
template <typename T, std::size_t N>
Vector<T, N> operator/(const Vector<T, N>& lhv, T rhd) {
  Vector<T, N> result{};

  for (std::size_t i{0}; i < N; ++i) {
    result[i] = lhv[i] / rhd;
  }

  return result;
}

// Dot product (algebraic)
template <typename T, std::size_t N>
T operator*(const Vector<T, N>& lhv, const Vector<T, N>& rhv) {
  T result{};

  for (std::size_t i{0}; i < N; ++i) {
    result += lhv[i] * rhv[i];
  }

  return result;
}

// Cross product
template <typename T, std::size_t N>
Vector<T, N> cross(const Vector<T, N>& lhv, const Vector<T, N>& rhv) {
  // clang-format off
  return {lhv[1] * rhv[2] - lhv[2] * rhv[1],
          lhv[2] * rhv[0] - lhv[0] * rhv[2],
          lhv[0] * rhv[1] - lhv[1] * rhv[0]};
  // clang-format on
}

// Norm
template <typename T, std::size_t N>
T norm(const Vector<T, N>& v) {
  return std::sqrt(v * v);
}

// Normalize vector
template <typename T, std::size_t N>
Vector<T, N> normalize(const Vector<T, N>& v) {
  return v / norm(v);
}

#endif
