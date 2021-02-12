#include "lambertian.hpp"

auto Lambertian::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> {
    if constexpr (DIFFUSE_RENDER_METHOD_TYPE == diffuse_render_method::true_lambertian_reflection) {
        const Vec3 direction = (rec.normal + Vec3::random_unit_vector()).unit();
        return std::optional(std::make_tuple(
            Ray(rec.p, direction, ray.time),
            albedo->value(rec.u, rec.v, rec.p),
            Vec3::dot(rec.normal, direction) / PI
        ));
    }
    else {
        const Vec3 direction = Vec3::random_in_hemisphere(rec.normal).unit();
        return std::optional(std::make_tuple(
            Ray(rec.p, direction, ray.time),
            albedo->value(rec.u, rec.v, rec.p),
            0.5 / PI
        ));
    }
}

auto Lambertian::scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 {
    const f64 cosine = Vec3::dot(rec.normal, scattered.direction.unit());
    return cosine < 0.0 ? 0.0 : cosine / PI;
}
