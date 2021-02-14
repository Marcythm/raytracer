#include "mixture_pdf.hpp"

auto MixturePDF::value(const Vec3 &direction) const -> f64 {
    return 0.5 * (pdf0->value(direction) + pdf1->value(direction));
}

auto MixturePDF::generate() const -> Vec3 {
    return ((random_f64() < 0.5) ? pdf0 : pdf1)->generate();
}
