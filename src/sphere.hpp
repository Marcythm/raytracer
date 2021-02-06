#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct Sphere: Hittable {
    p3d center;
    f64 radius;

    Sphere() = default;
    Sphere(const p3d &_center, const f64 _radius): center(_center), radius(_radius) {}
    ~Sphere() = default;

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, HitRecord> {
        const Vec3 oc = ray.origin() - center;
        const f64 a = ray.direction().length2();
        const f64 half_b = dot(oc, ray.direction());
        const f64 c = oc.length2() - radius * radius;
        const f64 discriminant = half_b * half_b - a * c;

        if (discriminant > 0) {
            const f64 root = std::sqrt(discriminant);

            if (const f64 t = (-half_b - root) / a; t_min < t and t < t_max) {
                HitRecord rec;
                rec.p = ray.at(t);
                rec.normal = (rec.p - center) / radius;
                rec.t = t;
                rec.set_face_normal(ray);
                return std::make_pair(true, rec);
            }
            if (const f64 t = (-half_b + root) / a; t_min < t and t < t_max) {
                HitRecord rec;
                rec.p = ray.at(t);
                rec.normal = (rec.p - center) / radius;
                rec.t = t;
                rec.set_face_normal(ray);
                return std::make_pair(true, rec);
            }
        }
        return std::make_pair(false, HitRecord());
    }
};
