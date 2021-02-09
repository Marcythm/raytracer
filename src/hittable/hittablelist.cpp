#include "hittablelist.hpp"

auto HittableList::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    std::optional<HitRecord> rec;
    f64 closest = t_max;

    for (const auto &hittable: hittables)
        if (const auto subrec = hittable->hit(ray, t_min, closest); subrec.has_value())
            closest = subrec.value().t, rec = subrec;

    return rec;
}

auto HittableList::bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> {
    if (hittables.empty()) return std::optional<AABB>();
    std::optional<AABB> box;

    for (const auto &hittable: hittables)
        if (const auto subbox = hittable->bounding_box(t0, t1); subbox.has_value()) {
            if (box.has_value())
                box.emplace(AABB::surrounding_box(box.value(), subbox.value()));
            else box = subbox;
        } else return std::optional<AABB>();

    return box;
}
