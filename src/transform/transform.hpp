#pragma once

#include "config.hpp"
#include "lib.hpp"
#include "ray.hpp"
#include "aabb.hpp"
#include "hittable.hpp"

struct Transform {
    virtual ~Transform() = default;

    virtual auto transform_point(const p3d &p) const -> p3d;
    virtual auto inverse_transform_point(const p3d &p) const -> p3d;

    virtual auto transform_vector(const Vec3 &v) const -> Vec3;
    virtual auto inverse_transform_vector(const Vec3 &v) const -> Vec3;

    virtual auto transform_ray(const Ray &ray) const -> Ray;
    virtual auto inverse_transform_ray(const Ray &ray) const -> Ray;

    virtual auto transform_box(const AABB &box) const -> AABB;
    virtual auto inverse_transform_box(const AABB &box) const -> AABB;
};
