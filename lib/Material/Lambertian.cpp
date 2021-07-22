#include "Material/Lambertian.hpp"
#include "Pdf/CosinePdf.hpp"

auto Lambertian::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> {
    return std::optional(ScatterRecord(
        albedo->value(rec.u, rec.v, rec.p),
        std::make_shared<CosinePDF>(rec.normal)
    ));
}

auto Lambertian::scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 {
    const f64 cosine = Vec3::dot(rec.normal, scattered.direction.unit());
    return cosine < 0.0 ? 0.0 : cosine / PI;
}
