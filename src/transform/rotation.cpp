#include "rotation.hpp"

/* RotationX */
RotationX::RotationX(const f64 _angle) {
    const f64 radian = deg2rad(_angle);
    sin_theta = std::sin(radian);
    cos_theta = std::cos(radian);
}

auto RotationX::transform_point(const p3d &p) const -> p3d {
    return p3d(
        p.x,
        cos_theta * p.y - sin_theta * p.z,
        sin_theta * p.y + cos_theta * p.z
    );
}

auto RotationX::inverse_transform_point(const p3d &p) const -> p3d {
    return p3d(
        p.x,
        sin_theta * p.z + cos_theta * p.y,
        cos_theta * p.z - sin_theta * p.y
    );
}

auto RotationX::transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        v.x,
        cos_theta * v.y - sin_theta * v.z,
        sin_theta * v.y + cos_theta * v.z
    );
}

auto RotationX::inverse_transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        v.x,
        sin_theta * v.z + cos_theta * v.y,
        cos_theta * v.z - sin_theta * v.y
    );
}

/* RotationY */
RotationY::RotationY(const f64 _angle) {
    const f64 radian = deg2rad(_angle);
    sin_theta = std::sin(radian);
    cos_theta = std::cos(radian);
}

auto RotationY::transform_point(const p3d &p) const -> p3d {
    return p3d(
        sin_theta * p.z + cos_theta * p.x,
        p.y,
        cos_theta * p.z - sin_theta * p.x
    );
}

auto RotationY::inverse_transform_point(const p3d &p) const -> p3d {
    return p3d(
        cos_theta * p.x - sin_theta * p.z,
        p.y,
        sin_theta * p.x + cos_theta * p.z
    );
}

auto RotationY::transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        sin_theta * v.z + cos_theta * v.x,
        v.y,
        cos_theta * v.z - sin_theta * v.x
    );
}

auto RotationY::inverse_transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        cos_theta * v.x - sin_theta * v.z,
        v.y,
        sin_theta * v.x + cos_theta * v.z
    );
}

/* RotationZ */
RotationZ::RotationZ(const f64 _angle) {
    const f64 radian = deg2rad(_angle);
    sin_theta = std::sin(radian);
    cos_theta = std::cos(radian);
}

auto RotationZ::transform_point(const p3d &p) const -> p3d {
    return p3d(
        cos_theta * p.x - sin_theta * p.y,
        sin_theta * p.x + cos_theta * p.y,
        p.z
    );
}

auto RotationZ::inverse_transform_point(const p3d &p) const -> p3d {
    return p3d(
        sin_theta * p.y + cos_theta * p.x,
        cos_theta * p.y - sin_theta * p.x,
        p.z
    );
}

auto RotationZ::transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        cos_theta * v.x - sin_theta * v.y,
        sin_theta * v.x + cos_theta * v.y,
        v.z
    );
}

auto RotationZ::inverse_transform_vector(const Vec3 &v) const -> Vec3 {
    return Vec3(
        sin_theta * v.y + cos_theta * v.x,
        cos_theta * v.y - sin_theta * v.x,
        v.z
    );
}
