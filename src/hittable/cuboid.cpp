#include "cuboid.hpp"

Cuboid::Cuboid(const p3d &p0, const p3d &p1, const ptr<Material> &material): min(p0), max(p1) {
    surfaces.push(XYAARectangle(min.x, max.x, min.y, max.y, min.z, material));
    surfaces.push(XYAARectangle(min.x, max.x, min.y, max.y, max.z, material));

    surfaces.push(YZAARectangle(min.y, max.y, min.z, max.z, min.x, material));
    surfaces.push(YZAARectangle(min.y, max.y, min.z, max.z, max.x, material));

    surfaces.push(ZXAARectangle(min.z, max.z, min.x, max.x, min.y, material));
    surfaces.push(ZXAARectangle(min.z, max.z, min.x, max.x, max.y, material));
}

auto Cuboid::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    return surfaces.hit(ray, t_min, t_max);
}

auto Cuboid::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(min, max);
}
