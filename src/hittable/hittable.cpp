#include "hittable.hpp"

auto HitRecord::set_face_normal(const Ray &ray) -> void {
    front_face = (Vec3::dot(ray.direction, normal) < 0);
    if (not front_face) normal = -normal;
}

auto Hittable::pdf_value(const p3d &origin, const Vec3 &direction) const -> f64 {
    return 0.0;
}

auto Hittable::random(const p3d &origin) const -> Vec3 {
    return Vec3(1.0, 0.0, 0.0);
}

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

auto HittableList::pdf_value(const p3d &origin, const Vec3 &direction) const -> f64 {
    f64 sum = 0.0;
    for (const auto &hittable: hittables)
        sum += hittable->pdf_value(origin, direction);
    return sum / hittables.size();
}

auto HittableList::random(const p3d &origin) const -> Vec3 {
    return hittables[random_i32(0, static_cast<i32>(hittables.size()) - 1)]->random(origin);
}
