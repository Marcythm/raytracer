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


auto YZAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (x - ray.origin.x) / ray.direction.x;
    if (t_min <= t and t <= t_max) {
        const p3d p = ray.at(t);
        if (y0 <= p.y and p.y <= y1 and z0 <= p.z and p.z <= z1) {
            HitRecord rec;
            rec.p = p;
            rec.normal = Vec3(1.0, 0.0, 0.0);
            rec.t = t;
            rec.u = (p.y - y0) / (y1 - y0);
            rec.v = (p.z - z0) / (z1 - z0);
            rec.material = material;
            rec.set_face_normal(ray);
            return rec;
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto YZAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(p3d(x - EPS, y0, z0), p3d(x + EPS, y1, z1));
}


auto ZXAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (y - ray.origin.y) / ray.direction.y;
    if (t_min <= t and t <= t_max) {
        const p3d p = ray.at(t);
        if (z0 <= p.z and p.z <= z1 and x0 <= p.x and p.x <= x1) {
            HitRecord rec;
            rec.p = p;
            rec.normal = Vec3(0.0, 1.0, 0.0);
            rec.t = t;
            rec.u = (p.z - z0) / (z1 - z0);
            rec.v = (p.x - x0) / (x1 - x0);
            rec.material = material;
            rec.set_face_normal(ray);
            return rec;
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto ZXAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(p3d(x0, y - EPS, z0), p3d(x1, y + EPS, z1));
}
