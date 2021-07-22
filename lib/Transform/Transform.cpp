#include "Transform/Transform.hpp"

auto Transform::transform_point(const P3d &p) const -> P3d { return p; }
auto Transform::inverse_transform_point(const P3d &p) const -> P3d { return p; }

auto Transform::transform_vector(const Vec3 &v) const -> Vec3 { return v; }
auto Transform::inverse_transform_vector(const Vec3 &v) const -> Vec3 { return v; }

auto Transform::transform_ray(const Ray &ray) const -> Ray {
    return Ray(transform_point(ray.origin), transform_vector(ray.direction), ray.time);
}
auto Transform::inverse_transform_ray(const Ray &ray) const -> Ray {
    return Ray(inverse_transform_point(ray.origin), inverse_transform_vector(ray.direction), ray.time);
}

auto Transform::transform_box(const AABB &box) const -> AABB {
    P3d min( INF,  INF,  INF);
    P3d max(-INF, -INF, -INF);

    for (i32 i = 0; i < 2; ++i)
        for (i32 j = 0; j < 2; ++j)
            for (i32 k = 0; k < 2; ++k) {
                const P3d transformed_p = transform_point(P3d(box[i].x, box[j].y, box[k].z));

                for (i32 axis = 0; axis < 3; ++axis) {
                    if (min[axis] > transformed_p[axis])
                        min[axis] = transformed_p[axis];
                    if (max[axis] < transformed_p[axis])
                        max[axis] = transformed_p[axis];
                }
            }

    return AABB(min, max);
}
auto Transform::inverse_transform_box(const AABB &box) const -> AABB {
    P3d min( INF,  INF,  INF);
    P3d max(-INF, -INF, -INF);

    for (i32 i = 0; i < 2; ++i)
        for (i32 j = 0; j < 2; ++j)
            for (i32 k = 0; k < 2; ++k) {
                const P3d invserse_transformed_p = inverse_transform_point(P3d(box[i].x, box[j].y, box[k].z));

                for (i32 axis = 0; axis < 3; ++axis) {
                    if (min[axis] > invserse_transformed_p[axis])
                        min[axis] = invserse_transformed_p[axis];
                    if (max[axis] < invserse_transformed_p[axis])
                        max[axis] = invserse_transformed_p[axis];
                }
            }

    return AABB(min, max);
}
