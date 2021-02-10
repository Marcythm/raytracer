#include "solid_color.hpp"

auto SolidColor::value(const f64, const f64, const p3d &) const -> RGB {
    return color;
}
