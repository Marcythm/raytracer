#include "Hittable/AARectangle.hpp"

auto XYAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (z - ray.origin.z) / ray.direction.z;
    if (t_min <= t and t <= t_max) {
        const P3d p = ray.at(t);
        if (x0 <= p.x and p.x <= x1 and y0 <= p.y and p.y <= y1) {
            return std::optional(HitRecord(
                p,
                Vec3(0.0, 0.0, 1.0),
                t,
                (p.x - x0) / (x1 - x0),
                (p.y - y0) / (y1 - y0),
                material,
                ray
            ));
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto XYAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(P3d(x0, y0, z - EPS), P3d(x1, y1, z + EPS));
}

auto XYAARectangle::pdf_value(const P3d &origin, const Vec3 &direction) const -> f64 {
    if (const auto &rec_op = hit(Ray(origin, direction, 0.0), EPS, INF); rec_op.has_value()) {
        const auto &rec = rec_op.value();

        const f64 area = (x1 - x0) * (y1 - y0);
        const f64 distance_squared = rec.t * rec.t * direction.length2();
        const f64 cosine = std::fabs(Vec3::dot(direction, rec.normal) / direction.length());

        return distance_squared / (cosine * area);
    } return 0.0;
}

auto XYAARectangle::random(const P3d &origin) const -> Vec3 {
    return P3d(random_f64(x0, x1), random_f64(y0, y1), z) - origin;
}


auto YZAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (x - ray.origin.x) / ray.direction.x;
    if (t_min <= t and t <= t_max) {
        const P3d p = ray.at(t);
        if (y0 <= p.y and p.y <= y1 and z0 <= p.z and p.z <= z1) {
            return std::optional(HitRecord(
                p,
                Vec3(1.0, 0.0, 0.0),
                t,
                (p.y - y0) / (y1 - y0),
                (p.z - z0) / (z1 - z0),
                material,
                ray
            ));
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto YZAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(P3d(x - EPS, y0, z0), P3d(x + EPS, y1, z1));
}

auto YZAARectangle::pdf_value(const P3d &origin, const Vec3 &direction) const -> f64 {
    if (const auto &rec_op = hit(Ray(origin, direction, 0.0), EPS, INF); rec_op.has_value()) {
        const auto &rec = rec_op.value();

        const f64 area = (y1 - y0) * (z1 - z0);
        const f64 distance_squared = rec.t * rec.t * direction.length2();
        const f64 cosine = std::fabs(Vec3::dot(direction, rec.normal) / direction.length());

        return distance_squared / (cosine * area);
    } return 0.0;
}

auto YZAARectangle::random(const P3d &origin) const -> Vec3 {
    return P3d(x, random_f64(y0, y1), random_f64(z0, z1)) - origin;
}


auto ZXAARectangle::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const f64 t = (y - ray.origin.y) / ray.direction.y;
    if (t_min <= t and t <= t_max) {
        const P3d p = ray.at(t);
        if (z0 <= p.z and p.z <= z1 and x0 <= p.x and p.x <= x1) {
            return std::optional(HitRecord(
                p,
                Vec3(0.0, 1.0, 0.0),
                t,
                (p.z - z0) / (z1 - z0),
                (p.x - x0) / (x1 - x0),
                material,
                ray
            ));
        } return std::optional<HitRecord>();
    } return std::optional<HitRecord>();
}

auto ZXAARectangle::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return AABB(P3d(x0, y - EPS, z0), P3d(x1, y + EPS, z1));
}

auto ZXAARectangle::pdf_value(const P3d &origin, const Vec3 &direction) const -> f64 {
    if (const auto &rec_op = hit(Ray(origin, direction, 0.0), EPS, INF); rec_op.has_value()) {
        const auto &rec = rec_op.value();

        const f64 area = (z1 - z0) * (x1 - x0);
        const f64 distance_squared = rec.t * rec.t * direction.length2();
        const f64 cosine = std::fabs(Vec3::dot(direction, rec.normal) / direction.length());

        return distance_squared / (cosine * area);
    } return 0.0;
}

auto ZXAARectangle::random(const P3d &origin) const -> Vec3 {
    return P3d(random_f64(x0, x1), y, random_f64(z0, z1)) - origin;
}
