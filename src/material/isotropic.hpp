#pragma once

#include "material.hpp"
#include "solid_color.hpp"

struct Isotropic: Material {
    ptr<Texture> albedo;

public:
    Isotropic(const ptr<Texture> &_albedo): albedo(_albedo) {}
    Isotropic(const RGB &_color): albedo(std::make_shared<SolidColor>(_color)) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
};
