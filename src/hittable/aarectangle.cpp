#include "aarectangle.hpp"

auto XYAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (z - ray.origin.z) / ray.direction.z;
    if (t_min <= t and t <= t_max) {
        const p3d p = ray.at(t);
        if (x0 <= p.x and p.x <= x1 and y0 <= p.y and p.y <= y1) {
            HitRecord rec;
            rec.p = p;
            rec.normal = Vec3(0.0, 0.0, 1.0);
            rec.t = t;
            rec.u = (p.x - x0) / (x1 - x0);
            rec.v = (p.y - y0) / (y1 - y0);
            rec.material = material;
            rec.set_face_normal(ray);
            return rec;
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto XYAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(p3d(x0, y0, z - EPS), p3d(x1, y1, z + EPS));
}
