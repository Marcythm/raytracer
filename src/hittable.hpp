#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

struct hit_record {
    p3d p;
    Vec3 normal;
    f64 t;

    hit_record() = default;
    hit_record(const p3d &_p, const Vec3 &_normal, const f64 _t): p(_p), normal(_normal), t(_t) {}
};

struct hittable {
    virtual auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, hit_record> = 0;
};
