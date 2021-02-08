use std::ops::{Neg, Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign};
use crate::utilities::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Vec3(f64, f64, f64);

impl Vec3 {
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self(x, y, z)
    }

    pub fn x(&self) -> f64 {
        self.0
    }
    pub fn y(&self) -> f64 {
        self.1
    }
    pub fn z(&self) -> f64 {
        self.2
    }

    pub fn length(&self) -> f64 { self.length2().sqrt() }
    pub fn length2(&self) -> f64 { self.0 * self.0 + self.1 * self.1 + self.2 * self.2 }

    pub fn unit(&self) -> Self { *self / self.length() }

    pub fn dot(u: Self, v: Self) -> f64 {
        u.0 * v.0 + u.1 * v.1 + u.2 * v.2
    }
    pub fn cross(u: Self, v: Self) -> Self {
        Self(
            u.1 * v.2 - u.2 * v.1,
            u.2 * v.0 - u.0 * v.2,
            u.0 * v.1 - u.1 * v.0,
        )
    }

    pub fn reflect_on(self, normal: Self) -> Self {
        self - 2.0 * Self::dot(self, normal) * normal
    }
    pub fn refract_on(self, normal: Self, etai_over_etat: f64) -> Self {
        let cos_theta = Self::dot(-self, normal);
        let r_out_perp = etai_over_etat * (self + cos_theta * normal);
        let r_out_para = -(1.0 - r_out_perp.length2()).abs().sqrt() * normal;
        r_out_perp + r_out_para
    }
}

impl Vec3 {
    pub fn random(rng: &mut SmallRng, min: f64, max: f64) -> Self {
        Self(
            rng.gen_range(min, max),
            rng.gen_range(min, max),
            rng.gen_range(min, max),
        )
    }

    pub fn random_in_unit_sphere(rng: &mut SmallRng) -> Self {
        loop {
            let p = Self::random(rng, -1.0, 1.0);
            if p.length2() < 1.0 {
                return p;
            }
        }
    }

    pub fn random_unit_vector(rng: &mut SmallRng) -> Self {
        let a = rng.gen_range(0.0, 2.0 * PI);
        let z = rng.gen_range(-1.0, 1.0);
        let r = ((1.0 - z * z) as f64).sqrt();
        Self(r * a.cos(), r * a.sin(), z)
    }

    pub fn random_in_hemisphere(rng: &mut SmallRng, normal: Self) -> Self {
        let in_unit_sphere = Self::random_in_unit_sphere(rng);
        if Self::dot(in_unit_sphere, normal) > 0.0 {
            in_unit_sphere
        } else {
            -in_unit_sphere
        }
    }
}

impl Neg for Vec3 {
    type Output = Self;
    fn neg(self) -> Self::Output {
        Self(-self.0, -self.1, -self.2)
    }
}

impl Add for Vec3 {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self(
            self.0 + rhs.0,
            self.1 + rhs.1,
            self.2 + rhs.2,
        )
    }
}

impl AddAssign for Vec3 {
    fn add_assign(&mut self, rhs: Self) {
        self.0 += rhs.0;
        self.1 += rhs.1;
        self.2 += rhs.2;
    }
}

impl Sub for Vec3 {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        Self(
            self.0 - rhs.0,
            self.1 - rhs.1,
            self.2 - rhs.2,
        )
    }
}

impl SubAssign for Vec3 {
    fn sub_assign(&mut self, rhs: Self) {
        self.0 -= rhs.0;
        self.1 -= rhs.1;
        self.2 -= rhs.2;
    }
}

impl Mul<f64> for Vec3 {
    type Output = Self;
    fn mul(self, rhs: f64) -> Self::Output {
        Self(
            self.0 * rhs,
            self.1 * rhs,
            self.2 * rhs,
        )
    }
}

impl MulAssign<f64> for Vec3 {
    fn mul_assign(&mut self, rhs: f64) {
        self.0 *= rhs;
        self.1 *= rhs;
        self.2 *= rhs;
    }
}

impl Mul<Vec3> for f64 {
    type Output = Vec3;
    fn mul(self, rhs: Vec3) -> Self::Output {
        Vec3(
            self * rhs.0,
            self * rhs.1,
            self * rhs.2,
        )
    }
}

impl Div<f64> for Vec3 {
    type Output = Self;
    fn div(self, rhs: f64) -> Self::Output {
        Self(
            self.0 / rhs,
            self.1 / rhs,
            self.2 / rhs,
        )
    }
}

impl DivAssign<f64> for Vec3 {
    fn div_assign(&mut self, rhs: f64) {
        self.0 /= rhs;
        self.1 /= rhs;
        self.2 /= rhs;
    }
}
