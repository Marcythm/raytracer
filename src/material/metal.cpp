#include "metal.hpp"

auto Metal::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> {
    Vec3 reflected = ray.direction.unit().reflect_on(rec.normal) + fuzz * Vec3::random_in_unit_sphere();
    if (Vec3::dot(reflected, rec.normal) > 0.0)
        return std::optional(std::make_tuple(Ray(rec.p, reflected), albedo, 0.0));
    return std::optional<std::tuple<Ray, RGB, f64>>();
}
