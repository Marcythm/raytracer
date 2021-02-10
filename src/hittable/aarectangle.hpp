#pragma once

#include "hittable.hpp"

struct XYAARectangle: Hittable { // XY Axis-Aligned Rectangle
    f64 x0, x1;
    f64 y0, y1;
    f64 z;
    ptr<Material> material;

public:
    XYAARectangle() = default;
    XYAARectangle(const f64 _x0, const f64 _x1, const f64 _y0, const f64 _y1, const f64 _z, const ptr<Material> &_material)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), material(_material) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
