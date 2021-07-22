#pragma once

#include "Hittable/Hittable.hpp"
#include "Hittable/AARectangle.hpp"

struct Cuboid: Hittable {
    P3d min;
    P3d max;
    HittableList surfaces;

public:
    Cuboid() = default;
    Cuboid(const P3d &p0, const P3d &p1, const ptr<Material> &material);

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
