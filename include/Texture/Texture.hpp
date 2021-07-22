#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"

struct Texture {
    virtual ~Texture() = default;

    virtual auto value(const f64 u, const f64 v, const P3d &p) const -> RGB = 0;
};
