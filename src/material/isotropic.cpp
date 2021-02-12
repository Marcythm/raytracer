#include "isotropic.hpp"

auto Isotropic::scatter(const Ray &, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> {
    return std::optional(std::make_tuple(
        Ray(rec.p, Vec3::random_in_unit_sphere()),
        albedo->value(rec.u, rec.v, rec.p),
        0.0
    ));
}
