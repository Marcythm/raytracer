#pragma once

#include "material.hpp"
#include "solid_color.hpp"

struct Lambertian: Material {
    ptr<Texture> albedo;

public:
    Lambertian(const RGB &_albedo): albedo(std::make_shared<SolidColor>(_albedo)) {}
    Lambertian(const ptr<Texture> &_albedo): albedo(_albedo) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
};
