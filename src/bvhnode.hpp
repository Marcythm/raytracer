#pragma once

#include "config.hpp"
#include "hittable.hpp"
#include "hittablelist.hpp"
#include "aabb.hpp"

struct BVHNode: Hittable { // Bounding Volume Hierarchy
    ptr<Hittable> left;
    ptr<Hittable> right;
    AABB box;

public:
    BVHNode() = default;
    BVHNode(Vec<ptr<Hittable>> &hittables, i32 beg, i32 end, const f64 t0, const f64 t1);
    BVHNode(HittableList &list, const f64 t0, const f64 t1)
        : BVHNode(list.hittables, 0, list.hittables.size(), t0, t1) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override {
        if (not box.hit(ray, t_min, t_max))
            return std::optional<HitRecord>();
        const auto rec_l = left->hit(ray, t_min, t_max);
        const auto rec_r = right->hit(ray, t_min, rec_l.has_value() ? rec_l.value().t : t_max);
        return rec_r.has_value() ? rec_r : rec_l;
    }
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override {
        return std::optional(box);
    }
};
