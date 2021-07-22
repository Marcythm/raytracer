#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"
#include "Ray.hpp"
#include "AABB.hpp"
#include "Hittable/Hittable.hpp"

struct Transform {
    virtual ~Transform() = default;

    virtual auto transform_point(const P3d &p) const -> P3d;
    virtual auto inverse_transform_point(const P3d &p) const -> P3d;

    virtual auto transform_vector(const Vec3 &v) const -> Vec3;
    virtual auto inverse_transform_vector(const Vec3 &v) const -> Vec3;

    virtual auto transform_ray(const Ray &ray) const -> Ray;
    virtual auto inverse_transform_ray(const Ray &ray) const -> Ray;

    virtual auto transform_box(const AABB &box) const -> AABB;
    virtual auto inverse_transform_box(const AABB &box) const -> AABB;
};
