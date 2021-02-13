#include "lambertian.hpp"

auto Lambertian::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> {
    ONB basis(rec.normal);
    const Vec3 direction = basis.transform(Vec3::random_cosine_direction()).unit();
    return std::optional(std::make_tuple(
        Ray(rec.p, direction, ray.time),
        albedo->value(rec.u, rec.v, rec.p),
        Vec3::dot(basis.w, direction) / PI
    ));
}

auto Lambertian::scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 {
    const f64 cosine = Vec3::dot(rec.normal, scattered.direction.unit());
    return cosine < 0.0 ? 0.0 : cosine / PI;
}
