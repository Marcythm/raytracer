#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct Sphere: Hittable {
    p3d center;
    f64 radius;

    Sphere() = default;
    Sphere(const p3d &_center, const f64 _radius): center(_center), radius(_radius) {}
    ~Sphere() = default;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, HitRecord>;
};
