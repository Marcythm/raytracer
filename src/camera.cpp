#include "camera.hpp"

auto Camera::get_ray(const f64 s, const f64 t) const -> Ray {
    const Vec3 rd = lens_radius * Vec3::random_in_unit_disk();
    const Vec3 offset = u * rd.x + v * rd.y;
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical, random_f64(time0, time1));
}
