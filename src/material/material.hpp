#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"

#include "hittable.hpp"

#include "texture.hpp"

struct Material {
    virtual ~Material() = default;
    virtual auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> = 0;
    virtual auto emitted(const f64 u, const f64 v, const p3d &p) const -> RGB {
        return RGB(0.0, 0.0, 0.0);
    }
};
