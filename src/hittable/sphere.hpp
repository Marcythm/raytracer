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

    static auto get_sphere_uv(const Vec3 &normal) -> std::pair<f64, f64>;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;

    auto pdf_value(const p3d &origin, const Vec3 &direction) const -> f64 override;
    auto random(const p3d &origin) const -> Vec3 override;
};
