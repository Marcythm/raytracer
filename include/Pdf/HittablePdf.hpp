#pragma once

#include "Pdf/Pdf.hpp"
#include "Hittable/Hittable.hpp"

struct HittablePDF: PDF {
    P3d origin;
    ptr<Hittable> hittable;

public:
    HittablePDF(const P3d &_origin, const ptr<Hittable> &_hittable)
        : origin(_origin), hittable(_hittable) {}

    auto value(const Vec3 &direction) const -> f64 override;
    auto generate() const -> Vec3 override;
};
