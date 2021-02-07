#pragma once

#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"

class Dielectric: public Material {
    f64 refract_eta;

public:
    Dielectric(const f64 _refract_eta): refract_eta(_refract_eta) {}
    ~Dielectric() = default;

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override {
        return std::optional(std::make_pair(
            Ray(
                rec.p,
                ray.direction().unit().refract_on(rec.normal.unit(), rec.front_face ? (1.0 / refract_eta) : refract_eta)
            ),
            RGB(1.0, 1.0, 1.0)
        ));
    }
};
