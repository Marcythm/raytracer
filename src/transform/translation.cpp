#include "translation.hpp"

auto Translation::transform_point(const p3d &p) const -> p3d {
    return p + offset;
}

auto Translation::inverse_transform_point(const p3d &p) const -> p3d {
    return p - offset;
}

auto Translation::transform_vector(const Vec3 &v) const -> Vec3 {
    return v;
}

auto Translation::inverse_transform_vector(const Vec3 &v) const -> Vec3 {
    return v;
}

auto Translation::transform_box(const AABB &box) const -> AABB {
    return AABB(box.min + offset, box.max + offset);
}

auto Translation::inverse_transform_box(const AABB &box) const -> AABB {
    return AABB(box.min - offset, box.max - offset);
}
