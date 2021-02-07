#pragma once

#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Camera {
    p3d origin;
    Vec3 horizontal;
    Vec3 vertical;
    p3d lower_left_corner;

public:
    constexpr Camera(
        const p3d &lookfrom, const Vec3 &lookdir, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio
    ): origin(lookfrom) {
        const f64 theta = deg2rad(vertical_field_of_view);
        const f64 h = std::tan(theta / 2);
        const f64 viewport_height = 2 * h;
        const f64 viewport_width = aspect_ratio * viewport_height;

        const Vec3 w = (-lookdir).unit();
        const Vec3 u = cross(viewup, w).unit();
        const Vec3 v = cross(w, u);

        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }
    constexpr Camera(
        const p3d &lookfrom, const p3d &lookat, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio
    ): Camera(lookfrom, lookat - lookfrom, viewup, vertical_field_of_view, aspect_ratio) {}

    constexpr auto get_ray(const f64 u, const f64 v) const -> Ray {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical);
    }
};
