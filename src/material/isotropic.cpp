#include "isotropic.hpp"

auto Isotropic::scatter(const Ray &, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> {
    return std::optional(std::make_pair(
        Ray(rec.p, Vec3::random_in_unit_sphere()),
        albedo->value(rec.u, rec.v, rec.p)
    ));
}
