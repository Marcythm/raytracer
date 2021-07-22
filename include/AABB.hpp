#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"
#include "Ray.hpp"

// Axis-Aligned Bounding Box
struct AABB {
    using Self = AABB;

    P3d min;
    P3d max;

public:
    AABB() = default;
    AABB(const P3d &a, const P3d &b): min(a), max(b) {}

    auto operator [] (const i32 idx) -> P3d& { return idx == 0 ? min : max; }
    auto operator [] (const i32 idx) const -> P3d { return idx == 0 ? min : max; }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> bool;

    static auto surrounding_box(const Self &box0, const Self &box1) -> Self;
};
