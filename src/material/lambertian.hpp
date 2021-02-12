#pragma once

#include "material.hpp"
#include "texture.hpp"
#include "constant_texture.hpp"

struct Lambertian: Material {
    ptr<Texture> albedo;

public:
    Lambertian(const ptr<Texture> &_albedo): albedo(_albedo) {}
    Lambertian(const RGB &_color): albedo(std::make_shared<ConstantTexture>(_color)) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>> override;
    auto scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 override;
};
