use std::{fmt::{Display}, ops::{Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign}};
use super::prelude::*;

/// RGB color
#[derive(Debug, Clone, Copy, Default)]
pub struct RGB {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl RGB {
    pub fn new(r: f64, g: f64, b: f64) -> Self {
        Self { r, g, b }
    }
}

impl RGB {
    pub fn random(min: f64, max: f64, rng: &mut SmallRng) -> Self {
        Self {
            r: rng.gen_range(min..max),
            g: rng.gen_range(min..max),
            b: rng.gen_range(min..max),
        }
    }
}

impl Add for RGB {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self::Output {
            r: self.r + rhs.r,
            g: self.g + rhs.g,
            b: self.b + rhs.b,
        }
    }
}

impl AddAssign for RGB {
    fn add_assign(&mut self, rhs: Self) {
        self.r += rhs.r;
        self.g += rhs.g;
        self.b += rhs.b;
    }
}

impl Sub for RGB {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        Self::Output {
            r: self.r - rhs.r,
            g: self.g - rhs.g,
            b: self.b - rhs.b,
        }
    }
}

impl SubAssign for RGB {
    fn sub_assign(&mut self, rhs: Self) {
        self.r -= rhs.r;
        self.g -= rhs.g;
        self.b -= rhs.b;
    }
}

impl Mul for RGB {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self::Output {
            r: self.r * rhs.r,
            g: self.g * rhs.g,
            b: self.b * rhs.b,
        }
    }
}

impl MulAssign for RGB {
    fn mul_assign(&mut self, rhs: Self) {
        self.r *= rhs.r;
        self.g *= rhs.g;
        self.b *= rhs.b;
    }
}

impl Mul<f64> for RGB {
    type Output = Self;
    fn mul(self, rhs: f64) -> Self::Output {
        Self::Output {
            r: self.r * rhs,
            g: self.g * rhs,
            b: self.b * rhs,
        }
    }
}

impl MulAssign<f64> for RGB {
    fn mul_assign(&mut self, rhs: f64) {
        self.r *= rhs;
        self.g *= rhs;
        self.b *= rhs;
    }
}

impl Mul<RGB> for f64 {
    type Output = RGB;
    fn mul(self, rhs: RGB) -> Self::Output {
        Self::Output {
            r: self * rhs.r,
            g: self * rhs.g,
            b: self * rhs.b,
        }
    }
}

impl Div<f64> for RGB {
    type Output = Self;
    fn div(self, rhs: f64) -> Self::Output {
        Self::Output {
            r: self.r / rhs,
            g: self.g / rhs,
            b: self.b / rhs,
        }
    }
}

impl DivAssign<f64> for RGB {
    fn div_assign(&mut self, rhs: f64) {
        self.r /= rhs;
        self.g /= rhs;
        self.b /= rhs;
    }
}

impl Display for RGB {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{} {} {}",
            (256.0 * if self.r.is_nan() { 0.0 } else { self.r }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
            (256.0 * if self.g.is_nan() { 0.0 } else { self.g }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
            (256.0 * if self.b.is_nan() { 0.0 } else { self.b }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
        )
    }
}

impl From<RGB> for [u8; 3] {
    fn from(col: RGB) -> Self {
        [
            (256.0 * if col.r.is_nan() { 0.0 } else { col.r }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
            (256.0 * if col.g.is_nan() { 0.0 } else { col.g }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
            (256.0 * if col.b.is_nan() { 0.0 } else { col.b }.powf(1.0 / GAMMA).clamp(0.0, 0.999)) as u8,
        ]
    }
}
