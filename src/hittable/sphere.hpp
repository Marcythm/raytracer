#pragma once

#include "hittable.hpp"

struct Sphere: Hittable {
    p3d center;
    f64 radius;
    ptr<Material> material;

public:
    Sphere() = default;
    Sphere(const p3d &_center, const f64 _radius, const ptr<Material> &_material)
        : center(_center), radius(_radius), material(_material) {}
    ~Sphere() = default;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
