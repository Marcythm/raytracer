#pragma once

#include "pdf.hpp"
#include "hittable.hpp"

struct HittablePDF: PDF {
    p3d origin;
    ptr<Hittable> hittable;

public:
    HittablePDF(const p3d &_origin, const ptr<Hittable> &_hittable)
        : origin(_origin), hittable(_hittable) {}

    auto value(const Vec3 &direction) const -> f64 override;
    auto generate() const -> Vec3 override;
};
