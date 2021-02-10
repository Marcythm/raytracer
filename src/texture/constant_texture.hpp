#pragma once

#include "texture.hpp"

struct ConstantTexture: Texture {
    RGB color;

public:
    // ConstantTexture() = default;
    ConstantTexture(const RGB &_color): color(_color) {}
    ConstantTexture(const f64 r, const f64 g, const f64 b): color(r, g, b) {}

    auto value(const f64, const f64, const p3d &) const -> RGB override;
};
