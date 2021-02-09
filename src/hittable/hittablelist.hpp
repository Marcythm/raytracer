#pragma once

#include "config.hpp"
#include "ray.hpp"
#include "hittable.hpp"

struct HittableList: Hittable {
    Vec<ptr<Hittable>> objects;

public:
    HittableList() = default;
    ~HittableList() = default;

    auto clear() -> void { objects.clear(); }
    template <typename T>
    auto push(const T &obj) -> void {
        if constexpr (std::is_convertible_v<T, ptr<Hittable>>)
            objects.push_back(obj);
        else {
            static_assert(std::is_base_of_v<Hittable, T>, "try to add an object which is not hittable into a hittable list");
            objects.emplace_back(std::make_shared<T>(obj));
        }
    }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
