#include "lambertian.hpp"

auto Lambertian::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> {
    if constexpr (constants::diffuse_render_method_type == diffuse_render_method::true_lambertian_reflection)
        return std::optional(std::make_pair(Ray(rec.p, rec.normal + Vec3::random_unit_vector(), ray.time), albedo));
    else
        return std::optional(std::make_pair(Ray(rec.p, Vec3::random_in_hemisphere(rec.normal), ray.time), albedo));
}
