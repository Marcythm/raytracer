#include "lambertian.hpp"

auto Lambertian::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> {
    if constexpr (DIFFUSE_RENDER_METHOD_TYPE == diffuse_render_method::true_lambertian_reflection)
        return std::optional(std::make_pair(
            Ray(rec.p, rec.normal + Vec3::random_unit_vector(), ray.time),
            albedo->value(rec.u, rec.v, rec.p)
        ));
    else
        return std::optional(std::make_pair(
            Ray(rec.p, Vec3::random_in_hemisphere(rec.normal), ray.time),
            albedo->value(rec.u, rec.v, rec.p)
        ));
}
