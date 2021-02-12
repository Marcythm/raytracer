#pragma once

#include "config.hpp"
#include "lib.hpp"
#include "aabb.hpp"
#include "hittable.hpp"

struct BVHNode: Hittable { // Bounding Volume Hierarchy
    ptr<Hittable> left;
    ptr<Hittable> right;
    AABB box;

public:
    BVHNode() = default;
    BVHNode(HittableList &list, const f64 t0, const f64 t1)
        : BVHNode(list.hittables, 0, list.hittables.size(), t0, t1) {}
    BVHNode(Vec<ptr<Hittable>> &hittables, i32 beg, i32 end, const f64 t0, const f64 t1);

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64, const f64) const -> std::optional<AABB> override {
        return std::optional(box);
    }
};
