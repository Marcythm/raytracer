use std::ops::{Neg, Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign, Index, IndexMut};
use crate::utilities::prelude::*;

/// vector in three-dimensional space
#[derive(Debug, Clone, Copy, Default)]
pub struct Vec3 {
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

impl Vec3 {
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self { x, y, z }
    }

    pub fn length(&self) -> f64 { self.length2().sqrt() }
    pub fn length2(&self) -> f64 { self.x * self.x + self.y * self.y + self.z * self.z }

    pub fn unit(&self) -> Self { *self / self.length() }

    pub fn dot(&self, rhs: Self) -> f64 {
        self.x * rhs.x + self.y * rhs.y + self.z * rhs.z
    }
    pub fn cross(&self, rhs: Self) -> Self {
        Self {
            x: self.y * rhs.z - self.z * rhs.y,
            y: self.z * rhs.x - self.x * rhs.z,
            z: self.x * rhs.y - self.y * rhs.x,
        }
    }

    pub fn reflect_on(&self, normal: Self) -> Self {
        *self - 2.0 * self.dot(normal) * normal
    }
    pub fn refract_on(&self, normal: Self, etai_over_etat: f64) -> Self {
        let cos_theta = (-*self).dot(normal);
        let r_out_perp = etai_over_etat * (*self + cos_theta * normal);
        let r_out_para = -(1.0 - r_out_perp.length2()).abs().sqrt() * normal;
        r_out_perp + r_out_para
    }
}

impl Vec3 {
    pub fn random(min: f64, max: f64, rng: &mut SmallRng) -> Self {
        Self {
            x: rng.gen_range(min, max),
            y: rng.gen_range(min, max),
            z: rng.gen_range(min, max),
        }
    }

    pub fn random_in_unit_sphere(rng: &mut SmallRng) -> Self {
        loop {
            let p = Self::random( -1.0, 1.0, rng);
            if p.length2() < 1.0 {
                return p;
            }
        }
    }

    pub fn random_unit_vector(rng: &mut SmallRng) -> Self {
        let a = rng.gen_range(0.0, 2.0 * PI);
        let z = rng.gen_range(-1.0, 1.0);
        let r = ((1.0 - z * z) as f64).sqrt();

        Self {
            x: r * a.cos(),
            y: r * a.sin(),
            z,
        }
    }

    pub fn random_in_hemisphere(rng: &mut SmallRng, normal: Self) -> Self {
        let in_unit_sphere = Self::random_in_unit_sphere(rng);
        if in_unit_sphere.dot(normal) > 0.0 {
            in_unit_sphere
        } else {
            -in_unit_sphere
        }
    }

    pub fn random_in_unit_disk(rng: &mut SmallRng) -> Self {
        loop {
            let p = Self {
                x: rng.gen_range(-1.0, 1.0),
                y: rng.gen_range(-1.0, 1.0),
                z: 0.0,
            };
            if p.length2() < 1.0 {
                return p;
            }
        }
    }

    pub fn random_cosine_direction(rng: &mut SmallRng) -> Self {
        let r1: f64 = rng.gen_range(0.0, 1.0);
        let r2: f64 = rng.gen_range(0.0, 1.0);

        let phi = 2.0 * PI * r1;
        let tmp = r2.sqrt();

        Self {
            x: phi.cos() * tmp,
            y: phi.sin() * tmp,
            z: (1.0 - r2).sqrt(),
        }
    }
}

impl Neg for Vec3 {
    type Output = Self;
    fn neg(self) -> Self::Output {
        Self::Output {
            x: -self.x,
            y: -self.y,
            z: -self.z,
        }
    }
}

impl Add for Vec3 {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self::Output {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
        }
    }
}

impl AddAssign for Vec3 {
    fn add_assign(&mut self, rhs: Self) {
        self.x += rhs.x;
        self.y += rhs.y;
        self.z += rhs.z;
    }
}

impl Sub for Vec3 {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        Self::Output {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
            z: self.z - rhs.z,
        }
    }
}

impl SubAssign for Vec3 {
    fn sub_assign(&mut self, rhs: Self) {
        self.x -= rhs.x;
        self.y -= rhs.y;
        self.z -= rhs.z;
    }
}

impl Mul<f64> for Vec3 {
    type Output = Self;
    fn mul(self, rhs: f64) -> Self::Output {
        Self::Output {
            x: self.x * rhs,
            y: self.y * rhs,
            z: self.z * rhs,
        }
    }
}

impl MulAssign<f64> for Vec3 {
    fn mul_assign(&mut self, rhs: f64) {
        self.x *= rhs;
        self.y *= rhs;
        self.z *= rhs;
    }
}

impl Mul<Vec3> for f64 {
    type Output = Vec3;
    fn mul(self, rhs: Vec3) -> Self::Output {
        Self::Output {
            x: self * rhs.x,
            y: self * rhs.y,
            z: self * rhs.z,
        }
    }
}

impl Div<f64> for Vec3 {
    type Output = Self;
    fn div(self, rhs: f64) -> Self::Output {
        Self::Output {
            x: self.x / rhs,
            y: self.y / rhs,
            z: self.z / rhs,
        }
    }
}

impl DivAssign<f64> for Vec3 {
    fn div_assign(&mut self, rhs: f64) {
        self.x /= rhs;
        self.y /= rhs;
        self.z /= rhs;
    }
}

impl Index<i32> for Vec3 {
    type Output = f64;
    fn index(&self, index: i32) -> &Self::Output {
        match index {
            0 => &self.x,
            1 => &self.y,
            _ => &self.z,
        }
    }
}

impl IndexMut<i32> for Vec3 {
    fn index_mut(&mut self, index: i32) -> &mut Self::Output {
        match index {
            0 => &mut self.x,
            1 => &mut self.y,
            _ => &mut self.z,
        }
    }
}
