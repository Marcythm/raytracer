#pragma once

#include "config.hpp"
#include "lib.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct Material {
    virtual ~Material() = default;

    virtual auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<std::tuple<Ray, RGB, f64>>;
    virtual auto emitted(const f64, const f64, const p3d &) const -> RGB;

    virtual auto scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64;
};
