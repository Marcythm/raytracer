#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"
#include "Hittable/Hittable.hpp"

struct Ray {
    using Self = Ray;

    P3d origin;
    Vec3 direction;
    f64 time;

public:
    Ray() = default;
    Ray(const Self &other): origin(other.origin), direction(other.direction), time(other.time) {}
    Ray(const P3d &ori, const Vec3 &dir, const f64 t = 0.0): origin(ori), direction(dir), time(t) {}
    Ray(const P3d &src, const P3d &dst, const f64 t = 0.0): origin(src), direction(dst - src), time(t) {}

    auto at(const f64 t) const -> P3d { return origin + t * direction; }

    auto color(const Hittable &world, const RGB &background, const ptr<Hittable> &lights, const i32 depth) const -> RGB;
};
