#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"

struct Ray {
    using Self = Ray;

    p3d origin;
    Vec3 direction;
    f64 time;

public:
    constexpr Ray(): time(0.0) { }
    constexpr Ray(const Self &other): origin(other.origin), direction(other.direction), time(other.time) {}
    constexpr Ray(const p3d &ori, const Vec3 &dir, const f64 t = 0.0): origin(ori), direction(dir), time(t) {}
    constexpr Ray(const p3d &src, const p3d &dst, const f64 t = 0.0): origin(src), direction(dst - src), time(t) {}

    constexpr auto at(const f64 t) const -> p3d { return origin + t * direction; }

    auto color(const Hittable &world, const i32 depth) const -> RGB;
};
