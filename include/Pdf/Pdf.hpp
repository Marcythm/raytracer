#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"

struct PDF {
    virtual ~PDF() = default;
    virtual auto value(const Vec3 &direction) const -> f64 = 0;
    virtual auto generate() const -> Vec3 = 0;
};
