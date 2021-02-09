#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

struct AABB { // Axis-Aligned Bounding Box
    p3d min;
    p3d max;

public:
    AABB() = default;
    AABB(const p3d &a, const p3d &b): min(a), max(b) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> bool {
        f64 tmin = t_min, tmax = t_max;
        for (i32 i = 0; i < 3; ++i) {
            const f64 inv_d = 1.0 / ray.direction[i];
            f64 t0 = (min[i] - ray.origin[i]) * inv_d;
            f64 t1 = (max[i] - ray.origin[i]) * inv_d;
            if (inv_d < 0.0) std::swap(t0, t1);
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin)
                return false;
        }
        return true;
    }

};
