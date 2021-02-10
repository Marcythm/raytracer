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

struct YZAARectangle: Hittable { // YZ Axis-Aligned Rectangle
    f64 y0, y1;
    f64 z0, z1;
    f64 x;
    ptr<Material> material;

public:
    YZAARectangle() = default;
    YZAARectangle(const f64 _y0, const f64 _y1, const f64 _z0, const f64 _z1, const f64 _x, const ptr<Material> &_material)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), material(_material) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};

struct ZXAARectangle: Hittable { // ZX Axis-Aligned Rectangle
    f64 z0, z1;
    f64 x0, x1;
    f64 y;
    ptr<Material> material;

public:
    ZXAARectangle() = default;
    ZXAARectangle(const f64 _z0, const f64 _z1, const f64 _x0, const f64 _x1, const f64 _y, const ptr<Material> &_material)
        : z0(_z0), z1(_z1), x0(_x0), x1(_x1), y(_y), material(_material) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
