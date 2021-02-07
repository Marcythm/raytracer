#include "config.hpp"
#include "lib.hpp"

#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "camera.hpp"

#include "hittable.hpp"
#include "sphere.hpp"
#include "hittablelist.hpp"

auto HittableList::hit(const Ray &ray, const f64 t_min, const f64 t_max) const -> std::optional<HitRecord> {
    std::optional<HitRecord> sol;
    f64 closest = t_max;

    for (const auto &obj: objects)
        if (const auto subsol = obj->hit(ray, t_min, closest); subsol.has_value())
            closest = subsol.value().t, sol = subsol;

    return sol;
}
