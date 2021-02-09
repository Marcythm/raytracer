#pragma once

#include "material.hpp"

struct Metal: Material {
    RGB albedo;
    f64 fuzz;

public:
    Metal(const RGB &_albedo, const f64 f = 0): albedo(_albedo), fuzz(f < 1 ? f : 1) {}
    ~Metal() = default;

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
};
