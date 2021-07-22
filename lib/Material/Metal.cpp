#include "Material/Metal.hpp"

auto Metal::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> {
    const Vec3 reflected = ray.direction.unit().reflect_on(rec.normal) + fuzz * Vec3::random_in_unit_sphere();
    if (Vec3::dot(reflected, rec.normal) > 0.0)
        return std::optional(ScatterRecord(
            albedo,
            Ray(rec.p, reflected, ray.time)
        ));
    return std::optional<ScatterRecord>();
}
