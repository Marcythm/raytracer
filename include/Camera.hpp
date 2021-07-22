#pragma once

#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec3.hpp"
#include "Utility/P3d.hpp"
#include "Utility/RGB.hpp"
#include "Utility/ONB.hpp"
#include "Ray.hpp"

struct Camera {
    P3d origin;
    Vec3 horizontal, vertical;
    P3d lower_left_corner;
    Vec3 w, u, v;
    f64 lens_radius;
    f64 time0, time1;

public:
    Camera(
        const P3d &lookfrom, const Vec3 &lookdir, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0.0, const f64 t1 = 0.0
    );

    Camera(
        const P3d &lookfrom, const P3d &lookat, const Vec3 &viewup,
        const f64 vertical_field_of_view, const f64 aspect_ratio,
        const f64 aperture, const f64 focus_distance,
        const f64 t0 = 0.0, const f64 t1 = 0.0
    ): Camera(lookfrom, lookat - lookfrom, viewup, vertical_field_of_view, aspect_ratio, aperture, focus_distance, t0, t1) {}

    auto get_ray(const f64 s, const f64 t) const -> Ray;
};
