#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"

#include "hittable.hpp"

#include "texture.hpp"
#include "solidcolor.hpp"

struct Material {
    virtual ~Material() = default;
    virtual auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::pair<Ray, RGB>> = 0;
};
