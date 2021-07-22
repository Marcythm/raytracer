#include "Ray.hpp"
#include "Hittable/Hittable.hpp"
#include "Material/Material.hpp"
#include "Pdf/HittablePdf.hpp"
#include "Pdf/MixturePdf.hpp"

auto Ray::color(const Hittable &world, const RGB &background, const ptr<Hittable> &lights, const i32 depth) const -> RGB {
    if (depth <= 0) return RGB(0.0, 0.0, 0.0);
    if (const auto &hit = world.hit(*this, EPS, INF); hit.has_value()) {
        const auto &hit_rec = hit.value();
        const RGB emitted = hit_rec.material->emitted(*this, hit_rec, hit_rec.u, hit_rec.v, hit_rec.p);
        if (const auto &scatter = hit_rec.material->scatter(*this, hit_rec); scatter.has_value()) {
            if (const auto scatter_rec = scatter.value(); scatter_rec.is_specular) {
                return scatter_rec.attenuation
                     * scatter_rec.specular_ray.color(world, background, lights, depth - 1);
            } else {
                const MixturePDF pdf(
                    std::make_shared<HittablePDF>(hit_rec.p, lights),
                    scatter_rec.pdf
                );

                Ray scattered = Ray(hit_rec.p, pdf.generate(), time);

                return emitted
                    + scatter_rec.attenuation
                    * hit_rec.material->scattering_pdf(*this, hit_rec, scattered)
                    * scattered.color(world, background, lights, depth - 1)
                    / pdf.value(scattered.direction);
            }
        } else return emitted;
    } return background;
}
