#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"
#include "Ray.hpp"
#include "Hittable/Hittable.hpp"

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

    virtual auto emitted(const Ray &ray, const HitRecord &rec, const f64 u, const f64 v, const P3d &p) const -> RGB;
    virtual auto scatter(const Ray &ray, const HitRecord &rec) const -> std::optional<ScatterRecord>;
    virtual auto scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const -> f64;
};
