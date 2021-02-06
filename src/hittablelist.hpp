#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"

class HittableList: public Hittable {
    Vec<ptr<Hittable>> objects;

public:
    HittableList() = default;
    ~HittableList() = default;

    auto clear() -> void { objects.clear(); }
    auto push(const ptr<Hittable> obj) -> void { objects.push_back(obj); }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::pair<bool, HitRecord> {
        std::pair<bool, HitRecord> sol;
        f64 closest = t_max;

        for (const auto &obj: objects)
            if (const std::pair<bool, HitRecord> subsol = obj->hit(ray, t_min, closest); subsol.first)
                closest = subsol.second.t, sol = subsol;

        return sol;
    }
};
