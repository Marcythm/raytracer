#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class AABB { // Axis-Aligned Bounding Box
    p3d _min;
    p3d _max;

public:
    AABB() = default;
    AABB(const p3d &a, const p3d &b): _min(a), _max(b) {}

    auto min() -> p3d { return _min; }
    auto max() -> p3d { return _max; }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> bool {
        f64 tmin = t_min, tmax = t_max;
        for (i32 i = 0; i < 3; ++i) {
            const f64 t0 = (_min[i] - ray.origin()[i]) / ray.direction()[i];
            const f64 t1 = (_max[i] - ray.origin()[i]) / ray.direction()[i];
            tmin = std::fmax(tmin, std::fmin(t0, t1));
            tmax = std::fmin(tmax, std::fmax(t0, t1));
            if (tmax <= tmin)
                return false;
        }
        return true;
    }

};
