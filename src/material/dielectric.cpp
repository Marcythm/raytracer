#include "dielectric.hpp"

auto Dielectric::scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> {
    // assert(rec.normal.length2() == 1);
    const Vec3 unit_direction = ray.direction.unit();
    const f64 cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    const f64 sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
    const f64 etai_over_etat = rec.front_face ? (1.0 / refractive_index) : refractive_index;

    if (etai_over_etat * sin_theta > 1.0 or random_f64() < schlick(cos_theta, etai_over_etat))
        return std::optional(std::make_pair(
            Ray(rec.p, unit_direction.reflect_on(rec.normal)),
            RGB(1.0, 1.0, 1.0)
        ));

    return std::optional(std::make_pair(
        Ray(rec.p, unit_direction.refract_on(rec.normal.unit(), etai_over_etat)),
        RGB(1.0, 1.0, 1.0)
    ));
}
