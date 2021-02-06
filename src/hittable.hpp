#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

struct HitRecord {
    p3d p;
    Vec3 normal;
    f64 t;
    bool front_face;

    HitRecord() = default;
    HitRecord(const p3d &_p, const Vec3 &_normal, const f64 _t): p(_p), normal(_normal), t(_t), front_face(false) {}

    auto set_face_normal(const Ray &ray) -> void {
        front_face = (dot(ray.direction(), normal) < 0);
        if (not front_face) normal = -normal;
    }
};

struct Hittable {
    virtual auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, HitRecord> = 0;
};
