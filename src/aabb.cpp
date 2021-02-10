#include "aabb.hpp"

auto AABB::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> bool {
    f64 tmin = t_min, tmax = t_max;
    for (i32 i = 0; i < 3; ++i) {
        const f64 inv_d = 1.0 / ray.direction[i];
        f64 t0 = (min[i] - ray.origin[i]) * inv_d;
        f64 t1 = (max[i] - ray.origin[i]) * inv_d;
        if (inv_d < 0.0) std::swap(t0, t1);
        if (t0 > tmin) tmin = t0;
        if (t1 < tmax) tmax = t1;
        if (tmax <= tmin)
            return false;
    }
    return true;
}

auto AABB::surrounding_box(const Self &box0, const Self &box1) -> Self {
    return Self(
        p3d(
            std::fmin(box0.min.x, box1.min.x),
            std::fmin(box0.min.y, box1.min.y),
            std::fmin(box0.min.z, box1.min.z)
        ),
        p3d(
            std::fmax(box0.max.x, box1.max.x),
            std::fmax(box0.max.y, box1.max.y),
            std::fmax(box0.max.z, box1.max.z)
        )
    );
}
