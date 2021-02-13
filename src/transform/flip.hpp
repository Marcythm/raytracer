#pragma once

#include "transform.hpp"

struct Flip: Transform {
public:
    Flip() = default;

    auto transform_vector(const Vec3 &p) const -> Vec3 override;
    auto inverse_transform_vector(const Vec3 &p) const -> Vec3 override;

    auto transform_ray(const Ray &ray) const -> Ray override;
    auto inverse_transform_ray(const Ray &ray) const -> Ray override;

    auto transform_box(const AABB &box) const -> AABB override;
    auto inverse_transform_box(const AABB &box) const -> AABB override;
};
