#include "constant_texture.hpp"

auto ConstantTexture::value(const f64, const f64, const p3d &) const -> RGB {
    return color;
}
