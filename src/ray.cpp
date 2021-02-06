#include "rgb.hpp"
#include "ray.hpp"
#include "hittable.hpp"

auto Ray::color(const Hittable &world) -> RGB {
    if (const auto &[succ, rec] = world.hit(*this, 0.0, infinity); succ)
        return 0.5 * RGB(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    const f64 t = 0.5 * (direction().unit().y() + 1.0);
    return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}
