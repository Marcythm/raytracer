#pragma once

#include "config.hpp"
#include "ray.hpp"
#include "hittable.hpp"

class HittableList: public Hittable {
    Vec<ptr<Hittable>> objects;

public:
    HittableList() = default;
    ~HittableList() = default;

    auto clear() -> void { objects.clear(); }
    auto push(const ptr<Hittable> obj) -> void { objects.push_back(obj); }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
};
