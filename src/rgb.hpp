#pragma once

#include "config.hpp"
#include "lib.hpp"

class RGB {
    using Self = RGB;

    f64 pr, pg, pb;

public:
    constexpr RGB(): pr(0), pg(0), pb(0) {}
    constexpr RGB(const Self &other): pr(other.pr), pg(other.pg), pb(other.pb) {}
    constexpr RGB(f64 e0, f64 e1, f64 e2): pr(e0), pg(e1), pb(e2) {}

    constexpr auto r() const -> f64 { return pr; }
    constexpr auto g() const -> f64 { return pg; }
    constexpr auto b() const -> f64 { return pb; }

    constexpr auto operator = (const Self &rhs) -> Self& { return pr = rhs.pr, pg = rhs.pg, pb = rhs.pb, *this; }

    constexpr auto operator - () const -> Self { return RGB(-pr, -pg, -pb); }

    constexpr auto operator += (const Self &rhs) -> Self& { pr += rhs.pr; pg += rhs.pg; pb += rhs.pb; return *this; }
    constexpr auto operator -= (const Self &rhs) -> Self& { pr -= rhs.pr; pg -= rhs.pg; pb -= rhs.pb; return *this; }
    constexpr auto operator *= (const f64   rhs) -> Self& { pr *= rhs;    pg *= rhs;    pb *= rhs;    return *this; }
    constexpr auto operator /= (const f64   rhs) -> Self& { pr /= rhs;    pg /= rhs;    pb /= rhs;    return *this; }

public:
    friend constexpr auto operator + (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.pr + rhs.pr, lhs.pg + rhs.pg, lhs.pb + rhs.pb);
    }
    friend constexpr auto operator - (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.pr - rhs.pr, lhs.pg - rhs.pg, lhs.pb - rhs.pb);
    }
    friend constexpr auto operator * (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.pr * rhs.pr, lhs.pg * rhs.pg, lhs.pb * rhs.pb);
    }
    friend constexpr auto operator * (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.pr * rhs, lhs.pg * rhs, lhs.pb * rhs);
    }
    friend constexpr auto operator * (const f64   lhs, const Self &rhs) -> Self {
        return Self(lhs * rhs.pr, lhs * rhs.pg, lhs * rhs.pb);
    }
    friend constexpr auto operator / (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.pr / rhs, lhs.pg / rhs, lhs.pb / rhs);
    }

    friend auto operator << (std::ostream &o, const Self &rhs) -> std::ostream& {
        return o << static_cast<i32>(255.999 * rhs.pr) << ' '
                 << static_cast<i32>(255.999 * rhs.pg) << ' '
                 << static_cast<i32>(255.999 * rhs.pb);
    }
    auto print(std::ostream &o, const i32 samples_per_pixel, const f64 GAMMA) -> std::ostream& {
        return o << static_cast<i32>(256 * clamp(std::pow(pr / samples_per_pixel, 1 / GAMMA), 0.0, 0.999)) << ' '
                 << static_cast<i32>(256 * clamp(std::pow(pg / samples_per_pixel, 1 / GAMMA), 0.0, 0.999)) << ' '
                 << static_cast<i32>(256 * clamp(std::pow(pb / samples_per_pixel, 1 / GAMMA), 0.0, 0.999));
    }
};
