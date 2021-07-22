#include "Texture/NoiseTexture.hpp"

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

auto Perlin::perlin_interpolation(const Vec3 c[2][2][2], const f64 u, const f64 v, const f64 w) -> f64 {
    f64 uu = u * u * (3.0 - 2.0 * u);
    f64 vv = v * v * (3.0 - 2.0 * v);
    f64 ww = w * w * (3.0 - 2.0 * w);

    f64 accum = 0.0;
    for (i32 i = 0; i < 2; ++i)
        for (i32 j = 0; j < 2; ++j)
            for (i32 k = 0; k < 2; ++k)
                accum += (i * uu + (1 - i) * (1.0 - uu))
                       * (j * vv + (1 - j) * (1.0 - vv))
                       * (k * ww + (1 - k) * (1.0 - ww))
                       * Vec3::dot(c[i][j][k], Vec3(u - i, v - j, w - k));
    return accum;
}

Perlin::Perlin(): random(new Vec3[POINT_COUNT]),
    px(generate_permutation()), py(generate_permutation()), pz(generate_permutation()) {
        for (i32 i = 0; i < POINT_COUNT; ++i)
            random[i] = Vec3::random(-1.0, 1.0).unit();
}

Perlin::~Perlin() {
    delete[] random;
    delete[] px;
    delete[] py;
    delete[] pz;
}

auto Perlin::noise(const P3d &p) const -> f64 {
    f64 u = p.x - std::floor(p.x);
    f64 v = p.y - std::floor(p.y);
    f64 w = p.z - std::floor(p.z);

    const i32 i = std::floor(p.x);
    const i32 j = std::floor(p.y);
    const i32 k = std::floor(p.z);
    Vec3 c[2][2][2];

    for (i32 di = 0; di < 2; ++di)
        for (i32 dj = 0; dj < 2; ++dj)
            for (i32 dk = 0; dk < 2; ++dk)
                c[di][dj][dk] = random[
                    px[(i + di) & 255]
                xor py[(j + dj) & 255]
                xor pz[(k + dk) & 255]
                ];

    return perlin_interpolation(c, u, v, w);
}

auto Perlin::turbulence(const P3d &p, const i32 depth) const -> f64 {
    f64 accum = 0.0;
    P3d tmp_p = p;
    f64 weight = 1.0;

    for (i32 i = 0; i < depth; ++i) {
        accum += weight * noise(tmp_p);
        weight *= 0.5;
        tmp_p *= 2.0;
    }

    return std::fabs(accum);
}

auto NoiseTexture::value(const f64, const f64, const P3d &p) const -> RGB {
    return RGB(1.0, 1.0, 1.0) * 0.5 * (1.0 + std::sin(scale * p.z + 10.0 * noise.turbulence(p)));
}
