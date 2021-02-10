#include "bvhnode.hpp"

BVHNode::BVHNode(Vec<ptr<Hittable>> &hittables, i32 beg, i32 end, const f64 t0, const f64 t1) {
    if (const i32 len = end - beg; len <= 0) {
        return;
    } else if (len == 1) {
        left = right = hittables[beg];
        box = left->bounding_box(t0, t1).value();
    } else {
        const i32 axis = random_i32(0, 2);
        const auto cmp = [axis](const ptr<Hittable> &lhs, const ptr<Hittable> &rhs) {
            return lhs->bounding_box(0.0, 0.0).value().min[axis] < rhs->bounding_box(0.0, 0.0).value().min[axis];
        };

        if (len == 2) {
            left = hittables[beg];
            right = hittables[beg + 1];
            if (not cmp(left, right))
                std::swap(left, right);
        } else {
            std::sort(hittables.begin() + beg, hittables.begin() + end, cmp);
            const i32 mid = beg + len / 2;
            left = std::make_shared<BVHNode>(hittables, beg, mid, t0, t1);
            right = std::make_shared<BVHNode>(hittables, mid, end, t0, t1);
        }

        box = AABB::surrounding_box(
            left->bounding_box(t0, t1).value(),
            right->bounding_box(t0, t1).value()
        );
    }
}

auto BVHNode::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    if (not box.hit(ray, t_min, t_max))
        return std::optional<HitRecord>();
    const auto rec_l = left->hit(ray, t_min, t_max);
    const auto rec_r = right->hit(ray, t_min, rec_l.has_value() ? rec_l.value().t : t_max);
    return rec_r.has_value() ? rec_r : rec_l;
}
