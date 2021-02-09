#include "noisetexture.hpp"

std::random_device Perlin::seed;
std::mt19937 Perlin::rng(seed());

auto Perlin::generate_permutation() -> i32* {
    i32 *p = new i32[POINT_COUNT];
    for (i32 i = 0; i < POINT_COUNT; ++i)
        p[i] = i;
    std::shuffle(p, p + POINT_COUNT, rng);
    return p;
}

Perlin::Perlin(): random(new f64[POINT_COUNT]),
    px(generate_permutation()), py(generate_permutation()), pz(generate_permutation()) {
        for (i32 i = 0; i < POINT_COUNT; ++i)
            random[i] = random_f64();
}

Perlin::~Perlin() {
    delete[] random;
    delete[] px;
    delete[] py;
    delete[] pz;
}

auto Perlin::noise(const p3d &p) const -> f64 {
    // const f64 u = p.x - std::floor(p.x);
    // const f64 v = p.y - std::floor(p.y);
    // const f64 w = p.z - std::floor(p.z);

    const i32 i = static_cast<i32>(4 * p.x) & 255;
    const i32 j = static_cast<i32>(4 * p.y) & 255;
    const i32 k = static_cast<i32>(4 * p.z) & 255;

    return random[px[i] xor py[j] xor pz[k]];
}

auto NoiseTexture::value(const f64, const f64, const p3d &p) const -> RGB {
    return RGB(1.0, 1.0, 1.0) * noise.noise(p);
}
