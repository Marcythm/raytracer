#include "ray.hpp"

auto Ray::color(const Hittable &world, const i32 depth) const -> RGB {
    if (depth <= 0) return RGB(0, 0, 0);
    if (const auto &hit = world.hit(*this, EPS, INFINITY); hit.has_value()) {
        if (const auto &scatter = hit.value().material->scatter(*this, hit.value()); scatter.has_value()) {
            const auto &[scattered, attenuation] = scatter.value();
            return attenuation * scattered.color(world, depth - 1);
        } else return RGB(0, 0, 0);
    }
    const f64 t = 0.5 * (direction.unit().y + 1.0);
    return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}
