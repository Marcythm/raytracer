#pragma once

#include "material.hpp"
#include "texture.hpp"
#include "constant_texture.hpp"

struct DiffuseLight: Material {
    ptr<Texture> emit;

public:
    DiffuseLight(const ptr<Texture> &_emit): emit(_emit) {}
    DiffuseLight(const RGB &_color): emit(std::make_shared<ConstantTexture>(_color)) {}

    auto emitted(const f64 u, const f64 v, const p3d &p) const -> RGB override;
};
