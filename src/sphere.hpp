#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct sphere: hittable {
    p3d center;
    f64 radius;

    sphere() = default;
    sphere(const p3d &_center, const f64 _radius): center(_center), radius(_radius) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, hit_record> {
        const Vec3 oc = ray.origin() - center;
        const f64 a = ray.direction().length2();
        const f64 half_b = dot(oc, ray.direction());
        const f64 c = oc.length2() - radius * radius;
        const f64 discriminant = half_b * half_b - a * c;

        if (discriminant > 0) {
            const f64 root = std::sqrt(discriminant);

            if (const f64 t = (-half_b - root) / a; t_min < t and t < t_max)
                return std::make_pair(true, hit_record(ray.at(t), (ray.at(t) - center) / radius, t));
            if (const f64 t = (-half_b + root) / a; t_min < t and t < t_max)
                return std::make_pair(true, hit_record(ray.at(t), (ray.at(t) - center) / radius, t));
        }
        return std::make_pair(false, hit_record());
    }
};
