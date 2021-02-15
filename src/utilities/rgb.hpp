#pragma once

#include "config.hpp"
#include "utility.hpp"

// RGB color
struct RGB {
    using Self = RGB;

    f64 r, g, b;

public:
    constexpr RGB(): r(0.0), g(0.0), b(0.0) {}
    constexpr RGB(const Self &other): r(other.r), g(other.g), b(other.b) {}
    constexpr RGB(f64 _r, f64 _g, f64 _b): r(_r), g(_g), b(_b) {}

    constexpr auto operator = (const Self &rhs) -> Self& { return r = rhs.r, g = rhs.g, b = rhs.b, *this; }

    constexpr auto operator += (const Self &rhs) -> Self& { r += rhs.r; g += rhs.g; b += rhs.b; return *this; }
    constexpr auto operator -= (const Self &rhs) -> Self& { r -= rhs.r; g -= rhs.g; b -= rhs.b; return *this; }
    constexpr auto operator *= (const f64   rhs) -> Self& { r *= rhs;   g *= rhs;   b *= rhs;   return *this; }
    constexpr auto operator /= (const f64   rhs) -> Self& { r /= rhs;   g /= rhs;   b /= rhs;   return *this; }

public:
    friend constexpr auto operator + (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
    }
    friend constexpr auto operator - (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
    }
    friend constexpr auto operator * (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
    }
    friend constexpr auto operator * (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
    }
    friend constexpr auto operator * (const f64   lhs, const Self &rhs) -> Self {
        return Self(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b);
    }
    friend constexpr auto operator / (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs);
    }

    friend auto operator << (std::ostream &o, const Self &rhs) -> std::ostream& {
        return o << static_cast<i32>(256.0 * std::clamp(std::pow(rhs.r != rhs.r ? 0.0 : rhs.r, 1.0 / GAMMA), 0.0, 0.999)) << ' '
                 << static_cast<i32>(256.0 * std::clamp(std::pow(rhs.g != rhs.g ? 0.0 : rhs.g, 1.0 / GAMMA), 0.0, 0.999)) << ' '
                 << static_cast<i32>(256.0 * std::clamp(std::pow(rhs.b != rhs.b ? 0.0 : rhs.b, 1.0 / GAMMA), 0.0, 0.999));
    }

public:
    static auto random() -> Self {
        return Self(random_f64(), random_f64(), random_f64());
    }
    static auto random(const f64 min, const f64 max) -> Self {
        return Self(random_f64(min, max), random_f64(min, max), random_f64(min, max));
    }
};
