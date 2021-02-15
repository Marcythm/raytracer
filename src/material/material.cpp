#include "ray.hpp"
#include "material.hpp"

ScatterRecord::ScatterRecord(const RGB &_attenuation, const Ray &_specular_ray)
    : attenuation(_attenuation), is_specular(true), specular_ray(_specular_ray) {}
ScatterRecord::ScatterRecord(const RGB &_attenuation, const ptr<PDF> &_pdf)
    : attenuation(_attenuation), is_specular(false), pdf(_pdf) {}

auto Material::emitted(const Ray &, const HitRecord &, const f64, const f64, const p3d &) const -> RGB {
    return RGB(0.0, 0.0, 0.0);
}

auto Material::scatter(const Ray &, const HitRecord &) const -> std::optional<ScatterRecord> {
    return std::optional<ScatterRecord>();
}

auto Material::scattering_pdf(const Ray &, const HitRecord &, const Ray &) const -> f64 {
    return 0.0;
}
