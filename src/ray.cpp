#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"

auto Ray::color(const Hittable &world) -> RGB {
    if (const auto &[succ, rec] = world.hit(*this, 0.0, infinity); succ)
        return 0.5 * Ray(rec.p, rec.p + rec.normal + Vec3::random_in_unit_sphere()).color(world);
    const f64 t = 0.5 * (direction().unit().y() + 1.0);
    return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}
