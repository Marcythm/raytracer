#pragma once

#include "config.hpp"
#include "lib.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct ScatterRecord {
    RGB attenuation;
    bool is_specular;
    Ray specular_ray;
    ptr<PDF> pdf;

public:
    ScatterRecord(const RGB &_attenuation, const Ray &_specular_ray);
    ScatterRecord(const RGB &_attenuation, const ptr<PDF> &_pdf);
};

struct Material {
    virtual ~Material() = default;

    virtual auto emitted(const Ray &ray, const HitRecord &rec, const f64 u, const f64 v, const p3d &p) const -> RGB;
    virtual auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord>;
    virtual auto scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64;
};
