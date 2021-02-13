#include "cosine_pdf.hpp"

auto CosinePDF::value(const Vec3 &direction) const -> f64 {
    const f64 cosine = Vec3::dot(direction.unit(), basis.w);
    return (cosine <= 0.0) ? 0.0 : (cosine / PI);
}

auto CosinePDF::generate() const -> Vec3 {
    return basis.transform(Vec3::random_cosine_direction());
}
