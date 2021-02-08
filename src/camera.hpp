#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Camera {
    p3d origin;
    Vec3 horizontal, vertical;
    p3d lower_left_corner;
    Vec3 w, u, v;
    f64 lens_radius;
    f64 time0, time1;

public:
    constexpr Camera(
        const p3d &lookfrom, const Vec3 &lookdir, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0, const f64 t1 = 0
    ): origin(lookfrom),
        w(-lookdir.unit()), u(cross(viewup, w).unit()), v(cross(w, u)),
        lens_radius(aperture / 2), time0(t0), time1(t1) {
        const f64 theta = deg2rad(vertical_field_of_view);
        const f64 h = std::tan(theta / 2);
        const f64 viewport_height = 2 * h;
        const f64 viewport_width = aspect_ratio * viewport_height;

        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;
    }

    constexpr Camera(
        const p3d &lookfrom, const p3d &lookat, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0, const f64 t1 = 0
    ): Camera(lookfrom, lookat - lookfrom, viewup, vertical_field_of_view, aspect_ratio, aperture, focus_distance, t0, t1) {}

    auto get_ray(const f64 s, const f64 t) const -> Ray {
        const Vec3 rd = lens_radius * Vec3::random_in_unit_disk();
        const Vec3 offset = u * rd.x() + v * rd.y();
        return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical, random_f64(time0, time1));
    }
};
