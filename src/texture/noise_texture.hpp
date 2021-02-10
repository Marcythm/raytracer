#pragma once

#include "texture.hpp"

struct Perlin {
    static constexpr i32 POINT_COUNT = 256;
    Vec3 *random;
    i32 *px, *py, *pz;

    static std::random_device seed;
    static std::mt19937 rng;
    static auto generate_permutation() -> i32*;
    static auto trilinear_interpolation(const f64 c[2][2][2], const f64 u, const f64 v, const f64 w) -> f64;
    static auto perlin_interpolation(const Vec3 c[2][2][2], const f64 u, const f64 v, const f64 w) -> f64;

public:
    Perlin();
    ~Perlin();

    auto noise(const p3d &p) const -> f64;
    auto turbulence(const p3d &p, const i32 depth = 7) const -> f64;
};


struct NoiseTexture: Texture {
    Perlin noise;
    f64 scale;

public:
    NoiseTexture(): scale(1.0) {}
    NoiseTexture(const f64 _scale): scale(_scale) {}

    auto value(const f64 u, const f64 v, const p3d &p) const -> RGB override;
};
