#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"

auto Ray::color(const Hittable &world, const i32 depth) -> RGB {
    if (depth <= 0) return RGB(0, 0, 0);
    if (const auto &[succ, rec] = world.hit(*this, constants::eps, constants::infinity); succ)
        return 0.5 * Ray(rec.p, rec.p + rec.normal + Vec3::random_unit_vector()).color(world, depth - 1);
    const f64 t = 0.5 * (direction().unit().y() + 1.0);
    return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}
