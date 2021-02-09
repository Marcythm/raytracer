#include "checkertexture.hpp"

auto CheckerTexture::value(const f64 u, const f64 v, const p3d &p) const -> RGB {
    if (std::sin(10.0 * p.x) * std::sin(10.0 * p.y) * std::sin(10.0 * p.z) < 0.0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}
