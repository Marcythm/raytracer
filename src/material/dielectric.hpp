#pragma once

#include "material.hpp"


struct Dielectric: Material {
    f64 refractive_index;

public:
    Dielectric(const f64 _refractive_index): refractive_index(_refractive_index) {}
    ~Dielectric() = default;

    // probability of reflect
    static auto schlick(const f64 cosine, const f64 refractive_index) -> f64 {
        f64 r0 = (1 - refractive_index) / (1 + refractive_index);
        r0 *= r0;
        return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
};
