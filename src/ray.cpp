#include "ray.hpp"

auto Ray::color(const Hittable &world, const RGB &background, const i32 depth) const -> RGB {
    if (depth <= 0) return RGB(0.0, 0.0, 0.0);
    if (const auto &hit = world.hit(*this, EPS, INFINITY); hit.has_value()) {
        const auto &rec = hit.value();
        const RGB emitted = rec.material->emitted(rec.u, rec.v, rec.p);
        if (const auto &scatter = rec.material->scatter(*this, rec); scatter.has_value()) {
            const p3d on_light(random_f64(213.0, 343.0), 554.0, random_f64(227.0, 332.0));
            Vec3 to_light = on_light - rec.p;
            const f64 distance_squared = to_light.length2();
            to_light = to_light.unit();

            if (Vec3::dot(to_light, rec.normal) < 0.0)
                return emitted;

            const f64 light_area = (343.0 - 213.0) * (332.0 - 227.0);
            const f64 light_cosine = std::fabs(to_light.y);
            if (light_cosine < EPS)
                return emitted;

            auto [scattered, attenuation, pdf] = scatter.value();
            pdf = distance_squared / (light_cosine * light_area);
            scattered = Ray(rec.p, to_light, time);

            return emitted
                 + attenuation
                 * rec.material->scattering_pdf(*this, rec, scattered)
                 * scattered.color(world, background, depth - 1)
                 / pdf;
        } else return emitted;
    } return background;
}
