#pragma once

#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "material.hpp"

class Metal: public Material {
    RGB albedo;

public:
    Metal(const RGB &_albedo): albedo(_albedo) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override {
        Vec3 reflected = ray.direction().unit().reflect_on(rec.normal);
        if (dot(reflected, rec.normal) > 0)
            return std::optional(std::make_pair(Ray(rec.p, reflected), albedo));
        return std::optional<std::pair<Ray, RGB>>();
    }
};
