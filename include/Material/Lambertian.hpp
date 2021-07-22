#pragma once

#include "Material/Material.hpp"
#include "Texture/Texture.hpp"
#include "Texture/ConstantTexture.hpp"

struct Lambertian: Material {
    ptr<Texture> albedo;

public:
    Lambertian(const ptr<Texture> &_albedo): albedo(_albedo) {}
    Lambertian(const RGB &_color): albedo(std::make_shared<ConstantTexture>(_color)) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> override;
    auto scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64 override;
};
