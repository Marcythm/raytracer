#pragma once

#include "hittable.hpp"

struct MovingSphere: Hittable {
    p3d center0, center1;
    f64 time0, time1;
    f64 radius;
    ptr<Material> material;

public:
    MovingSphere() = default;
    MovingSphere(
        const p3d &_center0, const p3d &_center1,
        const f64 _t0, const f64 _t1,
        const f64 _radius, const ptr<Material> &_material
    ): center0(_center0), center1(_center1), time0(_t0), time1(_t1), radius(_radius), material(_material) {}

    auto center(const f64 time) const -> p3d {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }

    static auto get_sphere_uv(const Vec3 &normal) -> std::pair<f64, f64>;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
