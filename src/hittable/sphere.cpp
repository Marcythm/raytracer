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
            p3d p = ray.at(t);
            Vec3 normal = (p - center) / radius;
            const auto &[u, v] = get_sphere_uv(normal);
            return std::optional(HitRecord(p, normal, t, u, v, material, ray));
        }
        if (const f64 t = (-half_b + root) / a; t_min < t and t < t_max) {
            p3d p = ray.at(t);
            Vec3 normal = (p - center) / radius;
            const auto &[u, v] = get_sphere_uv(normal);
            return std::optional(HitRecord(p, normal, t, u, v, material, ray));
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

auto Sphere::pdf_value(const p3d &origin, const Vec3 &direction) const -> f64 {
    if (hit(Ray(origin, direction, 0.0), EPS, INF).has_value()) {
        const f64 cos_theta_max = std::sqrt(1.0 - radius * radius / (center - origin).length2());
        const f64 solid_angle = 2.0 * PI * (1.0 - cos_theta_max);
        return 1.0 / solid_angle;
    } else return 0;
}

auto Sphere::random(const p3d &origin) const -> Vec3 {
    const Vec3 direction = center - origin;
    return ONB(direction).transform(Vec3::random_to_sphere(radius, direction.length2()));
}
