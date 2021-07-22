#pragma once

#include "Material/Material.hpp"
#include "Texture/Texture.hpp"
#include "Texture/ConstantTexture.hpp"

struct DiffuseLight: Material {
    ptr<Texture> emit;

public:
    DiffuseLight(const ptr<Texture> &_emit): emit(_emit) {}
    DiffuseLight(const RGB &_color): emit(std::make_shared<ConstantTexture>(_color)) {}

    auto emitted(const Ray &ray, const HitRecord &rec, const f64 u, const f64 v, const P3d &p) const -> RGB override;
};
