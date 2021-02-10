#include "constant_medium.hpp"

auto ConstantMedium::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const auto &&rec_in_op = boundary->hit(ray, -INF, INF);
    if (not rec_in_op.has_value()) return std::move(rec_in_op);
    auto rec_in = rec_in_op.value();

    const auto &&rec_out_op = boundary->hit(ray, rec_in.t + EPS, INF);
    if (not rec_out_op.has_value()) return std::move(rec_out_op);
    auto rec_out = rec_out_op.value();

    if (rec_in.t  < t_min) rec_in.t  = t_min;
    if (rec_out.t > t_max) rec_out.t = t_max;
    if (rec_in.t >= rec_out.t) return std::optional<HitRecord>();
    if (rec_in.t < 0.0) rec_in.t = 0.0;

    const f64 ray_length = ray.direction.length();
    const f64 distance_in_medium = (rec_out.t - rec_in.t) * ray_length;
    const f64 hit_distance = negative_inverse_density * std::log(random_f64());
    if (hit_distance > distance_in_medium) return std::optional<HitRecord>();

    const f64 hit_time = rec_in.t + hit_distance / ray_length;
    HitRecord rec(ray.at(hit_time), Vec3::random_unit_vector(), hit_time, random_f64(), random_f64(), material, ray);
    return std::optional(rec);
}

auto ConstantMedium::bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> {
    return boundary->bounding_box(t0, t1);
}
