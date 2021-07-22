#pragma once

#include "Config.hpp"
#include "Utility/Vec3.hpp"

// Orthonormal Basis
struct ONB {
    Vec3 w, v, u;

public:
    ONB(): w(0.0, 0.0, 1.0), v(0.0, 1.0, 0.0), u(1.0, 0.0, 0.0) {}
    ONB(const Vec3 &normal):
        w(normal.unit()),
        v(Vec3::cross(w, (std::fabs(w.x) > 0.9) ? Vec3(0.0, 1.0, 0.0) : Vec3(1.0, 0.0, 0.0)).unit()),
        u(Vec3::cross(w, v).unit()) {}

    auto operator [] (const i32 idx) const -> Vec3 { return idx == 0 ? u : idx == 1 ? v : w; }

    auto location(const f64 x, const f64 y, const f64 z) const -> Vec3 {
        return x * u + y * v + z * w;
    }
    auto transform(const Vec3 &vec) const -> Vec3 {
        return vec.x * u + vec.y * v + vec.z * w;
    }
};
