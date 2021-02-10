#include "diffuse_light.hpp"

auto DiffuseLight::scatter(const Ray &, const HitRecord &) const -> std::optional<std::pair<Ray, RGB>> {
    return std::optional<std::pair<Ray, RGB>>();
}
auto DiffuseLight::emitted(const f64 u, const f64 v, const p3d &p) const -> RGB {
    return emit->value(u, v, p);
}
