#pragma once

#include "config.hpp"
#include "lib.hpp"

class Vec3 {
    using Self = Vec3;

    f64 px, py, pz;

public:
    constexpr Vec3(): px(0), py(0), pz(0) {}
    constexpr Vec3(const Self &other): px(other.px), py(other.py), pz(other.pz) {}
    constexpr Vec3(f64 e0, f64 e1, f64 e2): px(e0), py(e1), pz(e2) {}

    constexpr auto x() const -> f64 { return px; }
    constexpr auto y() const -> f64 { return py; }
    constexpr auto z() const -> f64 { return pz; }

    constexpr auto operator = (const Self &rhs) -> Self& { return px = rhs.px, py = rhs.py, pz = rhs.pz, *this; }
    constexpr auto operator - () const -> Self { return Vec3(-px, -py, -pz); }

    constexpr auto operator += (const Self &rhs) -> Self& { px += rhs.px; py += rhs.py; pz += rhs.pz; return *this; }
    constexpr auto operator -= (const Self &rhs) -> Self& { px -= rhs.px; py -= rhs.py; pz -= rhs.pz; return *this; }
    constexpr auto operator *= (const f64   rhs) -> Self& { px *= rhs;    py *= rhs;    pz *= rhs;    return *this; }
    constexpr auto operator /= (const f64   rhs) -> Self& { px /= rhs;    py /= rhs;    pz /= rhs;    return *this; }

    auto length()  const -> f64 { return std::sqrt(length2()); }
    constexpr auto length2() const -> f64 { return px * px + py * py + pz * pz; }

    auto unit() const -> Vec3 { return *this / length(); }

public:
    friend constexpr auto operator + (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.px + rhs.px, lhs.py + rhs.py, lhs.pz + rhs.pz);
    }
    friend constexpr auto operator - (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.px - rhs.px, lhs.py - rhs.py, lhs.pz - rhs.pz);
    }
    friend constexpr auto operator * (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.px * rhs.px, lhs.py * rhs.py, lhs.pz * rhs.pz);
    }
    friend constexpr auto operator * (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.px * rhs, lhs.py * rhs, lhs.pz * rhs);
    }
    friend constexpr auto operator * (const f64   lhs, const Self &rhs) -> Self {
        return Self(lhs * rhs.px, lhs * rhs.py, lhs * rhs.pz);
    }
    friend constexpr auto operator / (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.px / rhs, lhs.py / rhs, lhs.pz / rhs);
    }

    friend constexpr auto dot(const Self &lhs, const Self &rhs) -> f64 {
        return lhs.px * rhs.px + lhs.py * rhs.py + lhs.pz * rhs.pz;
    }

    friend constexpr auto cross(const Self &lhs, const Self &rhs) -> Self {
        return Self(
            lhs.py * rhs.pz - lhs.pz * rhs.py,
            lhs.pz * rhs.px - lhs.px * rhs.pz,
            lhs.px * rhs.py - lhs.py * rhs.px
        );
    }

    friend auto operator << (std::ostream &o, const Self &rhs) -> std::ostream& {
        return o << rhs.px << ' ' << rhs.py << ' ' << rhs.pz;
    }

public:
    static auto random() -> Self {
        return Self(random_f64(), random_f64(), random_f64());
    }
    static auto random(const f64 min, const f64 max) -> Self {
        return Self(random_f64(min, max), random_f64(min, max), random_f64(min, max));
    }
    static auto random_unit_vector() -> Self {
        const f64 a = random_f64(0, 2 * constants::pi);
        const f64 z = random_f64(-1, 1);
        const f64 r = std::sqrt(1 - z * z);
        return Self(r * std::cos(a), r * std::sin(a), z);
    }
    static auto random_in_unit_sphere() -> Self {
        for ( ; ; )
            if (Self p = random(-1, 1); p.length2() < 1)
                return p;
    }
    static auto random_in_hemisphere(const Vec3 &normal) -> Self {
        Self in_unit_sphere = random_in_unit_sphere();
        return (dot(in_unit_sphere, normal) > 0.0) ? in_unit_sphere : -in_unit_sphere;
    }
};
