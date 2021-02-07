#pragma once

#include "config.hpp"

inline auto deg2rad(const f64 deg) -> f64 { return deg * constants::pi / 180.0; }

inline auto random_f64() -> f64 {
    static std::uniform_real_distribution<f64> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline auto random_f64(const f64 min, const f64 max) -> f64 {
    return min + (max - min) * random_f64();
}

inline auto clamp(const f64 x, const f64 min, const f64 max) -> f64 {
    return x < min ? min : x > max ? max : x;
}
