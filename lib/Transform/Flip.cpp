#include "Transform/Flip.hpp"

auto Flip::transform_vector(const Vec3 &p) const -> Vec3 { return -p; }
auto Flip::inverse_transform_vector(const Vec3 &p) const -> Vec3 { return -p; }

auto Flip::transform_ray(const Ray &ray) const -> Ray { return ray; }
auto Flip::inverse_transform_ray(const Ray &ray) const -> Ray { return ray; }

auto Flip::transform_box(const AABB &box) const -> AABB { return box; }
auto Flip::inverse_transform_box(const AABB &box) const -> AABB { return box; }
