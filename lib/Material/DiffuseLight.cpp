#include "Material/DiffuseLight.hpp"

auto DiffuseLight::emitted(const Ray &ray, const HitRecord &rec, const f64 u, const f64 v, const P3d &p) const -> RGB {
    return emit->value(u, v, p);
}
