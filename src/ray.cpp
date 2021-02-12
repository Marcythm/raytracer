#include "ray.hpp"

auto Ray::color(const Hittable &world, const RGB &background, const i32 depth) const -> RGB {
    if (depth <= 0) return RGB(0.0, 0.0, 0.0);
    if (const auto &hit = world.hit(*this, EPS, INFINITY); hit.has_value()) {
        const auto &rec = hit.value();
        const RGB emitted = rec.material->emitted(rec.u, rec.v, rec.p);
        if (const auto &scatter = rec.material->scatter(*this, rec); scatter.has_value()) {
            const auto &[scattered, attenuation, pdf] = scatter.value();
            return emitted
                 + attenuation
                 * rec.material->scattering_pdf(*this, rec, scattered)
                 * scattered.color(world, background, depth - 1)
                 / pdf;
        } else return emitted;
    } return background;
}
