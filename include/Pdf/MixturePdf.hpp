#pragma once

#include "Pdf/Pdf.hpp"

struct MixturePDF: PDF {
    ptr<PDF> pdf0, pdf1;

public:
    MixturePDF(const ptr<PDF> &_pdf0, const ptr<PDF> &_pdf1)
        : pdf0(_pdf0), pdf1(_pdf1) {}

    auto value(const Vec3 &direction) const -> f64 override;
    auto generate() const -> Vec3 override;
};
