#include "Texture/ConstantTexture.hpp"

auto ConstantTexture::value(const f64, const f64, const P3d &) const -> RGB {
    return color;
}
