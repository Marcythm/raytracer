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
    constexpr Camera(const f64 vertical_field_of_view, const f64 aspect_ratio): origin(0, 0, 0) {
        const f64 theta = deg2rad(vertical_field_of_view);
        const f64 h = std::tan(theta / 2);
        const f64 viewport_height = 2 * h;
        const f64 viewport_width = aspect_ratio * viewport_height;

        const f64 focal_length = 1.0;

        horizontal = Vec3(viewport_width, 0.0, 0.0);
        vertical = Vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
    }

    constexpr auto get_ray(const f64 u, const f64 v) const -> Ray {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical);
    }
};
