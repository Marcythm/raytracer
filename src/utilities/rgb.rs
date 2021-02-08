use std::{fmt::{Display}, ops::{Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign}};
use crate::utilities::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct RGB(f64, f64, f64);

impl RGB {
    pub fn new(r: f64, g: f64, b: f64) -> Self {
        Self(r, g, b)
    }

    pub fn r(&self) -> f64 {
        self.0
    }
    pub fn g(&self) -> f64 {
        self.1
    }
    pub fn b(&self) -> f64 {
        self.2
    }
}

impl Add for RGB {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self(
            self.0 + rhs.0,
            self.1 + rhs.1,
            self.2 + rhs.2,
        )
    }
}

impl AddAssign for RGB {
    fn add_assign(&mut self, rhs: Self) {
        self.0 += rhs.0;
        self.1 += rhs.1;
        self.2 += rhs.2;
    }
}

impl Sub for RGB {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        Self(
            self.0 - rhs.0,
            self.1 - rhs.1,
            self.2 - rhs.2,
        )
    }
}

impl SubAssign for RGB {
    fn sub_assign(&mut self, rhs: Self) {
        self.0 -= rhs.0;
        self.1 -= rhs.1;
        self.2 -= rhs.2;
    }
}

impl Mul for RGB {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self(
            self.0 * rhs.0,
            self.1 * rhs.1,
            self.2 * rhs.2,
        )
    }
}

impl MulAssign for RGB {
    fn mul_assign(&mut self, rhs: Self) {
        self.0 *= rhs.0;
        self.1 *= rhs.1;
        self.2 *= rhs.2;
    }
}

impl Mul<f64> for RGB {
    type Output = Self;
    fn mul(self, rhs: f64) -> Self::Output {
        Self(
            self.0 * rhs,
            self.1 * rhs,
            self.2 * rhs,
        )
    }
}

impl MulAssign<f64> for RGB {
    fn mul_assign(&mut self, rhs: f64) {
        self.0 *= rhs;
        self.1 *= rhs;
        self.2 *= rhs;
    }
}

impl Mul<RGB> for f64 {
    type Output = RGB;
    fn mul(self, rhs: RGB) -> Self::Output {
        RGB(
            self * rhs.0,
            self * rhs.1,
            self * rhs.2,
        )
    }
}

impl Div<f64> for RGB {
    type Output = Self;
    fn div(self, rhs: f64) -> Self::Output {
        Self(
            self.0 / rhs,
            self.1 / rhs,
            self.2 / rhs,
        )
    }
}

impl DivAssign<f64> for RGB {
    fn div_assign(&mut self, rhs: f64) {
        self.0 /= rhs;
        self.1 /= rhs;
        self.2 /= rhs;
    }
}

impl Display for RGB {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{} {} {}",
            (256.0 * clamp(self.0 / SAMPLES_PER_PIXEL as f64, 0.0, 0.999)) as i32,
            (256.0 * clamp(self.1 / SAMPLES_PER_PIXEL as f64, 0.0, 0.999)) as i32,
            (256.0 * clamp(self.2 / SAMPLES_PER_PIXEL as f64, 0.0, 0.999)) as i32,
        )
    }
}
