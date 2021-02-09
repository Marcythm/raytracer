#include "sphere.hpp"

auto Sphere::get_sphere_uv(const Vec3 &normal) -> std::pair<f64, f64> {
    const f64 phi = std::atan2(normal.z, normal.x);
    const f64 theta = std::asin(normal.y);
    return std::pair(1.0 - (phi + PI) / (2.0 * PI), (theta + PI / 2.0) / PI);
}

auto Sphere::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    const Vec3 oc = ray.origin - center;
    const f64 a = ray.direction.length2();
    const f64 half_b = Vec3::dot(oc, ray.direction);
    const f64 c = oc.length2() - radius * radius;
    const f64 discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        const f64 root = std::sqrt(discriminant);

        if (const f64 t = (-half_b - root) / a; t_min < t and t < t_max) {
            HitRecord rec;
            rec.p = ray.at(t);
            rec.normal = (rec.p - center) / radius;
            rec.t = t;
            const auto &[u, v] = get_sphere_uv(rec.normal);
            rec.u = u;
            rec.v = v;
            rec.material = material;
            rec.set_face_normal(ray);
            return std::optional(rec);
        }
        if (const f64 t = (-half_b + root) / a; t_min < t and t < t_max) {
            HitRecord rec;
            rec.p = ray.at(t);
            rec.normal = (rec.p - center) / radius;
            rec.t = t;
            const auto &[u, v] = get_sphere_uv(rec.normal);
            rec.u = u;
            rec.v = v;
            rec.set_face_normal(ray);
            rec.material = material;
            return std::optional(rec);
        }
    }
    return std::optional<HitRecord>();
}

auto Sphere::bounding_box(const f64, const f64) const -> std::optional<AABB> {
    return std::optional(AABB(
        p3d(center.x - radius, center.y - radius, center.z - radius),
        p3d(center.x + radius, center.y + radius, center.z + radius)
    ));
}
