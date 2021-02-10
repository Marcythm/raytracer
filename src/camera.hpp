#pragma once

#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"

struct Camera {
    p3d origin;
    Vec3 horizontal, vertical;
    p3d lower_left_corner;
    Vec3 w, u, v;
    f64 lens_radius;
    f64 time0, time1;

public:
    Camera(
        const p3d &lookfrom, const Vec3 &lookdir, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0.0, const f64 t1 = 0.0
    ): origin(lookfrom),
        w(-lookdir.unit()), u(Vec3::cross(viewup, w).unit()), v(Vec3::cross(w, u)),
        lens_radius(aperture / 2.0), time0(t0), time1(t1) {
        const f64 theta = deg2rad(vertical_field_of_view);
        const f64 h = std::tan(theta / 2.0);
        const f64 viewport_height = 2.0 * h;
        const f64 viewport_width = aspect_ratio * viewport_height;

        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - focus_distance * w;
    }

    Camera(
        const p3d &lookfrom, const p3d &lookat, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0.0, const f64 t1 = 0.0
    ): Camera(lookfrom, lookat - lookfrom, viewup, vertical_field_of_view, aspect_ratio, aperture, focus_distance, t0, t1) {}

    auto get_ray(const f64 s, const f64 t) const -> Ray;
};
