#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"

class Ray {
    using Self = Ray;

    p3d _origin;
    Vec3 _direction;

public:
    constexpr Ray() { }
    constexpr Ray(const Self &other): _origin(other._origin), _direction(other._direction) {}
    constexpr Ray(const p3d &ori, const Vec3 &dir): _origin(ori), _direction(dir) {}
    constexpr Ray(const p3d &src, const p3d &dst): _origin(src), _direction(dst - src) {}

    constexpr auto origin() const -> p3d { return _origin; }
    constexpr auto direction() const -> Vec3 { return _direction; }

    constexpr auto at(const f64 t) const -> p3d { return _origin + t * _direction; }

    auto color(const Hittable &world, const i32 depth) const -> RGB;
};
