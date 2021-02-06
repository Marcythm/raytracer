#pragma once

#include "config.hpp"

constexpr f64 infinity = std::numeric_limits<f64>::infinity();
constexpr f64 pi = 3.1415926535897932385;

inline auto deg2rad(const f64 deg) -> f64 { return deg * pi / 180.0; }

inline auto random_f64() -> f64 {
    static std::uniform_real_distribution<f64> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline auto random_f64(const f64 min, const f64 max) -> f64 {
    return min + (max - min) * random_f64();
}

#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
