#pragma once

#include "Material/Material.hpp"

struct Metal: Material {
    RGB albedo;
    f64 fuzz;

public:
    Metal(const RGB &_albedo, const f64 f = 0.0): albedo(_albedo), fuzz(f < 1.0 ? f : 1.0) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> override;
};
