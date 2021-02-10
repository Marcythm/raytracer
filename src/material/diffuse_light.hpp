#pragma once

#include "material.hpp"
#include "solid_color.hpp"

struct DiffuseLight: Material {
    ptr<Texture> emit;

public:
    DiffuseLight(const ptr<Texture> &_emit): emit(_emit) {}
    DiffuseLight(const RGB &color): emit(std::make_shared<SolidColor>(color)) {}

    auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> override;
    auto emitted(const f64 u, const f64 v, const p3d &p) const -> RGB override;
};
