#pragma once

#include "config.hpp"
#include "utility.hpp"

struct Vec3 {
    using Self = Vec3;

    f64 x, y, z;

public:
    constexpr Vec3(): x(0), y(0), z(0) {}
    constexpr Vec3(const Self &other): x(other.x), y(other.y), z(other.z) {}
    constexpr Vec3(f64 _x, f64 _y, f64 _z): x(_x), y(_y), z(_z) {}

    constexpr auto operator = (const Self &rhs) -> Self& { return x = rhs.x, y = rhs.y, z = rhs.z, *this; }
    constexpr auto operator - () const -> Self { return Vec3(-x, -y, -z); }

    constexpr auto operator += (const Self &rhs) -> Self& { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
    constexpr auto operator -= (const Self &rhs) -> Self& { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
    constexpr auto operator *= (const f64   rhs) -> Self& { x *= rhs;   y *= rhs;   z *= rhs;   return *this; }
    constexpr auto operator /= (const f64   rhs) -> Self& { x /= rhs;   y /= rhs;   z /= rhs;   return *this; }

    constexpr auto operator [] (const i32 idx) -> f64& { return idx == 0 ? x : idx == 1 ? y : z; }
    constexpr auto operator [] (const i32 idx) const -> f64 { return idx == 0 ? x : idx == 1 ? y : z; }

    auto length()  const -> f64 { return std::sqrt(length2()); }
    constexpr auto length2() const -> f64 { return x * x + y * y + z * z; }

    auto unit() const -> Vec3 { return *this / length(); }
    auto reflect_on(const Self &normal) const -> Self { return *this - 2 * dot(*this, normal) * normal; }
    auto refract_on(const Self &normal, const f64 etai_over_etat) const -> Self {
        // assert(length2() == 1); assert(normal.length2() == 1);
        const f64 cos_theta = dot(-*this, normal);
        Vec3 r_out_perp = etai_over_etat * (*this + cos_theta * normal);
        Vec3 r_out_para = -std::sqrt(std::fabs(1.0 - r_out_perp.length2())) * normal;
        return r_out_perp + r_out_para;
    }

public:
    friend constexpr auto operator + (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }
    friend constexpr auto operator - (const Self &lhs, const Self &rhs) -> Self {
        return Self(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend constexpr auto operator * (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }
    friend constexpr auto operator * (const f64   lhs, const Self &rhs) -> Self {
        return Self(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }
    friend constexpr auto operator / (const Self &lhs, const f64   rhs) -> Self {
        return Self(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }

    friend constexpr auto dot(const Self &lhs, const Self &rhs) -> f64 {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    friend constexpr auto cross(const Self &lhs, const Self &rhs) -> Self {
        return Self(
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        );
    }

public:
    static auto random() -> Self {
        return Self(random_f64(), random_f64(), random_f64());
    }
    static auto random(const f64 min, const f64 max) -> Self {
        return Self(random_f64(min, max), random_f64(min, max), random_f64(min, max));
    }
    static auto random_unit_vector() -> Self {
        const f64 a = random_f64(0, 2 * PI);
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
    static auto random_in_unit_disk() -> Self {
        for ( ; ; )
            if (Self p(random_f64(-1, 1), random_f64(-1, 1), 0); p.length2() < 1)
                return p;
    }
};
