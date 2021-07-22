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
#include "Transform/Transform.hpp"

// Apply a transform to a hittable object
struct Instance: Hittable, Transform {
    ptr<Hittable> hittable;
    ptr<Transform> transform;

public:
    Instance() = default;
    Instance(const ptr<Hittable> &_hittable, const ptr<Transform> &_transform)
        : hittable(_hittable), transform(_transform) {}

public:
    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;

public:
    auto transform_point(const P3d &p) const -> P3d override {
        return transform->transform_point(p);
    }
    auto inverse_transform_point(const P3d &p) const -> P3d override {
        return transform->inverse_transform_point(p);
    }

    auto transform_vector(const Vec3 &v) const -> Vec3 override {
        return transform->transform_vector(v);
    }
    auto inverse_transform_vector(const Vec3 &v) const -> Vec3 override {
        return transform->inverse_transform_vector(v);
    }

    auto transform_ray(const Ray &ray) const -> Ray override {
        return transform->transform_ray(ray);
    }
    auto inverse_transform_ray(const Ray &ray) const -> Ray override {
        return transform->inverse_transform_ray(ray);
    }

    auto transform_box(const AABB &box) const -> AABB override {
        return transform->transform_box(box);
    }
    auto inverse_transform_box(const AABB &box) const -> AABB override {
        return transform->inverse_transform_box(box);
    }
};
