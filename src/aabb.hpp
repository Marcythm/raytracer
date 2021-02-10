#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"

struct AABB { // Axis-Aligned Bounding Box
    using Self = AABB;

    p3d min;
    p3d max;

public:
    AABB() = default;
    AABB(const p3d &a, const p3d &b): min(a), max(b) {}

    auto operator [] (const i32 idx) const -> p3d { return idx == 0 ? min : max; }
    auto operator [] (const i32 idx) -> p3d& { return idx == 0 ? min : max; }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> bool;

    static auto surrounding_box(const Self &box0, const Self &box1) -> Self;
};
