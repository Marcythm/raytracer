#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "ray.hpp"
#include "hittable.hpp"

class Sphere: public Hittable {
    p3d center;
    f64 radius;
    ptr<Material> material;

public:
    Sphere() = default;
    Sphere(const p3d &_center, const f64 _radius, const ptr<Material> &_material)
        : center(_center), radius(_radius), material(_material) {}
    ~Sphere() = default;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, HitRecord>;
};
