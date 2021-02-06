#pragma once

#include "config.hpp"

constexpr f64 infinity = std::numeric_limits<f64>::infinity();
constexpr f64 pi = 3.1415926535897932385;

inline auto deg2rad(const f64 deg) -> f64 { return deg * pi / 180.0; }

#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
