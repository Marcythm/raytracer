#pragma once

#include "Material/Material.hpp"
#include "Texture/Texture.hpp"
#include "Texture/ConstantTexture.hpp"

struct Isotropic: Material {
    ptr<Texture> albedo;

public:
    Isotropic(const ptr<Texture> &_albedo): albedo(_albedo) {}
    Isotropic(const RGB &_color): albedo(std::make_shared<ConstantTexture>(_color)) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord> override;
};
