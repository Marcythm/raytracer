#pragma once

#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"

class Metal: public Material {
    RGB albedo;
    f64 fuzz;

public:
    Metal(const RGB &_albedo, const f64 f = 0): albedo(_albedo), fuzz(f < 1 ? f : 1) {}
    ~Metal() = default;

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override {
        Vec3 reflected = ray.direction().unit().reflect_on(rec.normal) + fuzz * Vec3::random_in_unit_sphere();
        if (dot(reflected, rec.normal) > 0)
            return std::optional(std::make_pair(Ray(rec.p, reflected), albedo));
        return std::optional<std::pair<Ray, RGB>>();
    }
};
