#pragma once

#include "hittable.hpp"
#include "aarectangle.hpp"

struct Cuboid: Hittable {
    p3d min;
    p3d max;
    HittableList surfaces;

public:
    Cuboid() = default;
    Cuboid(const p3d &p0, const p3d &p1, const ptr<Material> &material);

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
