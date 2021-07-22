#include "Pdf/HittablePdf.hpp"

auto HittablePDF::value(const Vec3 &direction) const -> f64 {
    return hittable->pdf_value(origin, direction);
}
auto HittablePDF::generate() const -> Vec3 {
    return hittable->random(origin);
}
