#pragma once

#include "config.hpp"
#include "lib.hpp"

struct Texture {
    virtual ~Texture() = default;
    virtual auto value(const f64 u, const f64 v, const p3d &p) const -> RGB = 0;
};
