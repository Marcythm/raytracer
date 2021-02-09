#pragma once

#include "lib.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"

// probability of reflect
auto schlick(const f64 cosine, const f64 refractive_index) -> f64 {
    f64 r0 = (1 - refractive_index) / (1 + refractive_index);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

struct Dielectric: Material {
    f64 refractive_index;

public:
    Dielectric(const f64 _refractive_index): refractive_index(_refractive_index) {}
    ~Dielectric() = default;

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override {
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
};
