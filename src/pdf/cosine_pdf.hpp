#pragma once

#include "pdf.hpp"

struct CosinePDF: PDF {
    ONB basis;

public:
    CosinePDF(const Vec3 &normal): basis(normal) {}

    auto value(const Vec3 &direction) const -> f64 override;
    auto generate() const -> Vec3 override;
};
