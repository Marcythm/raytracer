#include "isotropic.hpp"

auto Isotropic::scatter(const Ray &, const HitRecord &rec) const -> std::optional<ScatterRecord> {
    return std::optional(ScatterRecord(
        albedo->value(rec.u, rec.v, rec.p),
        Ray(rec.p, Vec3::random_in_unit_sphere())
    ));
}
