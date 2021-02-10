#pragma once

#include "transform.hpp"

struct RotationX: Transform { // Rotation around X-axis
    f64 sin_theta;
    f64 cos_theta;

public:
    RotationX() = default;
    RotationX(const f64 _angle);

    auto transform_point(const p3d &p) const -> p3d override;
    auto inverse_transform_point(const p3d &p) const -> p3d override;

    auto transform_vector(const Vec3 &v) const -> Vec3 override;
    auto inverse_transform_vector(const Vec3 &v) const -> Vec3 override;
};

struct RotationY: Transform { // Rotation around Y-axis
    f64 sin_theta;
    f64 cos_theta;

public:
    RotationY() = default;
    RotationY(const f64 _angle);

    auto transform_point(const p3d &p) const -> p3d override;
    auto inverse_transform_point(const p3d &p) const -> p3d override;

    auto transform_vector(const Vec3 &v) const -> Vec3 override;
    auto inverse_transform_vector(const Vec3 &v) const -> Vec3 override;
};

struct RotationZ: Transform { // Rotation around Z-axis
    f64 sin_theta;
    f64 cos_theta;

public:
    RotationZ() = default;
    RotationZ(const f64 _angle);

    auto transform_point(const p3d &p) const -> p3d override;
    auto inverse_transform_point(const p3d &p) const -> p3d override;

    auto transform_vector(const Vec3 &v) const -> Vec3 override;
    auto inverse_transform_vector(const Vec3 &v) const -> Vec3 override;
};
