#pragma once

#include "transform.hpp"

struct Translation: Transform {
    Vec3 offset;

public:
    Translation() = default;
    Translation(const Vec3 &_offset): offset(_offset) {}

    auto transform_point(const p3d &p) const -> p3d override;
    auto inverse_transform_point(const p3d &p) const -> p3d override;

    auto transform_vector(const Vec3 &p) const -> Vec3 override;
    auto inverse_transform_vector(const Vec3 &p) const -> Vec3 override;

    auto transform_box(const AABB &box) const -> AABB override;
    auto inverse_transform_box(const AABB &box) const -> AABB override;
};
