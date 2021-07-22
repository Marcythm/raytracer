#pragma once

#include "Material/Material.hpp"

struct Dielectric: Material {
    f64 refractive_index;

public:
    Dielectric(const f64 _refractive_index): refractive_index(_refractive_index) {}

    // probability of reflect
    static auto schlick(const f64 cosine, const f64 refractive_index) -> f64 {
        f64 r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
        r0 *= r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
    }

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> override;
};
