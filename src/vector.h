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

  Vector<T, N> operator-() const {
    Vector<T, N> result{};

    for (std::size_t i{0}; i < N; ++i) {
      result[i] = -values[i];
    }

    return result;
  }
};

// Specializations for N = 2,3,4 replace the generic array-based layout with
// named members (x, y, z, w), enabling cleaner, semantically meaningful field
// access (v.x, v.y, v.z, v.w) without losing index-based access via operator[].
template <typename T>
struct Vector<T, 2> {
  T x{};
  T y{};

  T& operator[](std::size_t i) {
    assert(i < 2);
    return (i == 0 ? x : y);
  }

  const T& operator[](std::size_t i) const {
    assert(i < 2);
    return (i == 0 ? x : y);
  }

  Vector<T, 2> operator-() const { return {-x, -y}; }
};

template <typename T>
struct Vector<T, 3> {
  T x{};
  T y{};
  T z{};

  T& operator[](std::size_t i) {
    assert(i < 3);
    return (i == 0 ? x : (i == 1 ? y : z));
  }

  const T& operator[](std::size_t i) const {
    assert(i < 3);
    return (i == 0 ? x : (i == 1 ? y : z));
  }

  Vector<T, 3> operator-() const { return {-x, -y, -z}; }
};

template <typename T>
struct Vector<T, 4> {
  T x{};
  T y{};
  T z{};
  T w{};

  T& operator[](std::size_t i) {
    assert(i < 4);
    return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)));
  }

  const T& operator[](std::size_t i) const {
    assert(i < 4);
    return (i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)));
  }

  Vector<T, 4> operator-() const { return {-x, -y, -z, -w}; }
};

// clang-format off
using Vec2     = Vector<double, 2>;
using Vec3     = Vector<double, 3>;
using Vec4     = Vector<double, 4>;
using Coord3D  = Vector<double, 3>;
using PixelRGB = Vector<double, 3>;
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
