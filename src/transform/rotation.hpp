#pragma once

#include "transform.hpp"

// Rotation around X-axis
struct RotationX: Transform {
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

// Rotation around Y-axis
struct RotationY: Transform {
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

// Rotation around Z-axis
struct RotationZ: Transform {
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
