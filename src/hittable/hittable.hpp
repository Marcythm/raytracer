#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"
#include "aabb.hpp"

struct HitRecord {
    p3d p;
    Vec3 normal;
    f64 t;
    f64 u, v;
    ptr<Material> material;
    bool front_face;

    HitRecord() = default;
    HitRecord(const p3d &_p, const Vec3 &_normal, const f64 _t, const f64 _u, const f64 _v, const ptr<Material> &_material, const Ray &_ray)
        : p(_p), normal(_normal), t(_t), u(_u), v(_v), material(_material), front_face(false) {
            set_face_normal(_ray);
        }

    auto set_face_normal(const Ray &ray) -> void;
};

struct Hittable {
    virtual ~Hittable() = default;
    virtual auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> = 0;
    virtual auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> = 0;
};

struct HittableList: Hittable {
    Vec<ptr<Hittable>> hittables;

public:
    HittableList() = default;
    ~HittableList() = default;

    auto clear() -> void { hittables.clear(); }
    template <typename T>
    auto push(const T &hittable) -> void {
        if constexpr (std::is_convertible_v<T, ptr<Hittable>>)
            hittables.push_back(hittable);
        else {
            static_assert(std::is_base_of_v<Hittable, T>, "try to add an object which is not hittable into a hittable list");
            hittables.emplace_back(std::make_shared<T>(hittable));
        }
    }

    auto hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> override;
    auto bounding_box(const f64 t0, const f64 t1) const -> std::optional<AABB> override;
};
