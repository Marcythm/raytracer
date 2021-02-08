#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"

class Ray {
    using Self = Ray;

    p3d _origin;
    Vec3 _direction;
    f64 _time;

public:
    constexpr Ray(): _time(0.0) { }
    constexpr Ray(const Self &other): _origin(other._origin), _direction(other._direction), _time(other._time) {}
    constexpr Ray(const p3d &ori, const Vec3 &dir, const f64 t = 0.0): _origin(ori), _direction(dir), _time(t) {}
    constexpr Ray(const p3d &src, const p3d &dst, const f64 t = 0.0): _origin(src), _direction(dst - src), _time(t) {}

    constexpr auto origin() const -> p3d { return _origin; }
    constexpr auto direction() const -> Vec3 { return _direction; }
    constexpr auto time() const -> f64 { return _time; }

    constexpr auto at(const f64 t) const -> p3d { return _origin + t * _direction; }

    auto color(const Hittable &world, const i32 depth) const -> RGB;
};
