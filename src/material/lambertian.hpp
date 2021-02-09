#pragma once

#include "material.hpp"

struct Lambertian: Material {
    RGB albedo;

public:
    Lambertian(const RGB &_albedo): albedo(_albedo) {}
    ~Lambertian() = default;

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
};
