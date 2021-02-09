#include "metal.hpp"

auto Metal::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> {
    Vec3 reflected = ray.direction.unit().reflect_on(rec.normal) + fuzz * Vec3::random_in_unit_sphere();
    if (dot(reflected, rec.normal) > 0)
        return std::optional(std::make_pair(Ray(rec.p, reflected), albedo));
    return std::optional<std::pair<Ray, RGB>>();
}
