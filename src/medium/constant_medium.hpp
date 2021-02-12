#pragma once

#include "ray.hpp"
#include "aabb.hpp"
#include "medium.hpp"
#include "isotropic.hpp"

struct ConstantMedium: Medium {
    ptr<Hittable> boundary;
    ptr<Material> material;
    f64 negative_inverse_density;

public:
    ConstantMedium(const ptr<Hittable> &_boundary, const ptr<Texture> &_texture, const f64 _density)
        : boundary(_boundary), material(std::make_shared<Isotropic>(_texture)), negative_inverse_density(-1.0 / _density) {}
    ConstantMedium(const ptr<Hittable> &_boundary, const RGB &_color, const f64 _density)
        : boundary(_boundary), material(std::make_shared<Isotropic>(_color)), negative_inverse_density(-1.0 / _density) {}

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
