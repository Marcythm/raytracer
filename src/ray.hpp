#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "hittable.hpp"

#include "material.hpp"

struct Ray {
    using Self = Ray;

    p3d origin;
    Vec3 direction;
    f64 time;

public:
    Ray() = default;
    Ray(const Self &other): origin(other.origin), direction(other.direction), time(other.time) {}
    Ray(const p3d &ori, const Vec3 &dir, const f64 t = 0.0): origin(ori), direction(dir), time(t) {}
    Ray(const p3d &src, const p3d &dst, const f64 t = 0.0): origin(src), direction(dst - src), time(t) {}

    auto at(const f64 t) const -> p3d { return origin + t * direction; }

    auto color(const Hittable &world, const RGB &background, const i32 depth) const -> RGB;
};
