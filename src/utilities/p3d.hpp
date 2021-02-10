#pragma once

#include "config.hpp"
#include "vec3.hpp"

struct p3d {
    using Self = p3d;

    f64 x, y, z;

public:
    constexpr p3d(): x(0.0), y(0.0), z(0.0) {}
    constexpr p3d(const Self &other): x(other.x), y(other.y), z(other.z) {}
    constexpr p3d(f64 _x, f64 _y, f64 _z): x(_x), y(_y), z(_z) {}

    constexpr auto operator = (const Self &rhs) -> Self& { return x = rhs.x, y = rhs.y, z = rhs.z, *this; }

    constexpr auto operator += (const Vec3 &rhs) -> Self& { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
    constexpr auto operator -= (const Vec3 &rhs) -> Self& { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
    constexpr auto operator *= (const f64   rhs) -> Self& { x *= rhs;   y *= rhs;   z *= rhs;   return *this; }
    constexpr auto operator /= (const f64   rhs) -> Self& { x /= rhs;   y /= rhs;   z /= rhs;   return *this; }

    constexpr auto operator [] (const i32 idx) -> f64& { return idx == 0 ? x : idx == 1 ? y : z; }
    constexpr auto operator [] (const i32 idx) const -> f64 { return idx == 0 ? x : idx == 1 ? y : z; }

public:
    friend constexpr auto operator + (const Self &lhs, const Vec3 &rhs) -> Self {
        return Self(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }
    friend constexpr auto operator - (const Self &lhs, const Vec3 &rhs) -> Self {
        return Self(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend constexpr auto operator - (const Self &lhs, const Self &rhs) -> Vec3 {
        return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
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
};
