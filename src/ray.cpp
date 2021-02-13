#include "ray.hpp"
#include "cosine_pdf.hpp"

auto Ray::color(const Hittable &world, const RGB &background, const i32 depth) const -> RGB {
    if (depth <= 0) return RGB(0.0, 0.0, 0.0);
    if (const auto &hit = world.hit(*this, EPS, INFINITY); hit.has_value()) {
        const auto &rec = hit.value();
        const RGB emitted = rec.material->emitted(rec.u, rec.v, rec.p);
        if (const auto &scatter = rec.material->scatter(*this, rec); scatter.has_value()) {
            auto [scattered, attenuation, _] = scatter.value();
            const CosinePDF pdf(rec.normal);

            scattered = Ray(rec.p, pdf.generate(), time);

            return emitted
                 + attenuation
                 * rec.material->scattering_pdf(*this, rec, scattered)
                 * scattered.color(world, background, depth - 1)
                 / pdf.value(scattered.direction);
        } else return emitted;
    } return background;
}
