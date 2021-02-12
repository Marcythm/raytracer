#include "ray.hpp"
#include "material.hpp"

auto Material::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> {
    return std::optional<std::tuple<Ray, RGB, f64>>();
}
auto Material::scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 {
    return 0.0;
}
auto Material::emitted(const f64, const f64, const p3d &) const -> RGB {
    return RGB(0.0, 0.0, 0.0);
}
