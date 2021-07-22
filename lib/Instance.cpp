#include "Instance.hpp"

auto Instance::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    Ray inverse_transformed_ray = transform->inverse_transform_ray(ray);
    if (auto &&rec = hittable->hit(inverse_transformed_ray, t_min, t_max); rec.has_value()) {
        rec.value().p = transform->transform_point(rec.value().p);
        rec.value().normal = transform->transform_vector(rec.value().normal);
        rec.value().set_face_normal(inverse_transformed_ray);
        return std::move(rec);
    } else return std::move(rec);
}

auto Instance::bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> {
    if (auto &&box = hittable->bounding_box(t0, t1); box.has_value()) {
        box.value() = transform->transform_box(box.value());
        return std::move(box);
    } else return std::move(box);
}
