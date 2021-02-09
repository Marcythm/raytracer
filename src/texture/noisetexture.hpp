#pragma once

#include "texture.hpp"

struct Perlin {
    static constexpr i32 POINT_COUNT = 256;
    f64 *random;
    i32 *px, *py, *pz;

    static std::random_device seed;
    static std::mt19937 rng;
    static auto generate_permutation() -> i32*;

public:
    Perlin();
    ~Perlin();

    auto noise(const p3d &p) const -> f64;
};


struct NoiseTexture: Texture {
    Perlin noise;

public:
    NoiseTexture() = default;

    auto value(const f64 u, const f64 v, const p3d &p) const -> RGB override;
};
