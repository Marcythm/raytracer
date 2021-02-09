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

auto Perlin::trilinear_interpolation(const f64 c[2][2][2], const f64 u, const f64 v, const f64 w) -> f64 {
    f64 accum = 0.0;
    for (i32 i = 0; i < 2; ++i)
        for (i32 j = 0; j < 2; ++j)
            for (i32 k = 0; k < 2; ++k)
                accum += (i * u + (1 - i) * (1.0 - u))
                       * (j * v + (1 - j) * (1.0 - v))
                       * (k * w + (1 - k) * (1.0 - w))
                       * c[i][j][k];
    return accum;
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
    f64 u = p.x - std::floor(p.x); u = u * u * (3.0 - 2.0 * u);
    f64 v = p.y - std::floor(p.y); v = v * v * (3.0 - 2.0 * v);
    f64 w = p.z - std::floor(p.z); w = w * w * (3.0 - 2.0 * w);

    const i32 i = std::floor(p.x);
    const i32 j = std::floor(p.y);
    const i32 k = std::floor(p.z);
    f64 c[2][2][2];

    for (i32 di = 0; di < 2; ++di)
        for (i32 dj = 0; dj < 2; ++dj)
            for (i32 dk = 0; dk < 2; ++dk)
                c[di][dj][dk] = random[
                    px[(i + di) & 255]
                xor py[(j + dj) & 255]
                xor pz[(k + dk) & 255]
                ];

    return trilinear_interpolation(c, u, v, w);
}

auto NoiseTexture::value(const f64, const f64, const p3d &p) const -> RGB {
    return RGB(1.0, 1.0, 1.0) * noise.noise(scale * p);
}
