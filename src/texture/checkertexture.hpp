#pragma once

#include "texture.hpp"
#include "solidcolor.hpp"

struct CheckerTexture: Texture {
    ptr<Texture> even;
    ptr<Texture> odd;

public:
    CheckerTexture() = default;
    CheckerTexture(const RGB &col0, const RGB &col1)
        : even(std::make_shared<SolidColor>(col0)), odd(std::make_shared<SolidColor>(col1)) {}
    CheckerTexture(const ptr<Texture> &t0, const ptr<Texture> &t1)
        : even(t0), odd(t1) {}

    auto value(const f64, const f64, const p3d &) const -> RGB override;
};
