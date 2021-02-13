#pragma once

#include "config.hpp"
#include "lib.hpp"

struct PDF {
    virtual ~PDF() = default;
    virtual auto value(const Vec3 &direction) const -> f64 = 0;
    virtual auto generate() const -> Vec3 = 0;
};
