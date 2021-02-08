use std::ops::{Add, AddAssign, Sub, SubAssign};

use crate::utilities::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct P3d(f64, f64, f64);

impl P3d {
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
}

impl Add<Vec3> for P3d {
    type Output = Self;
    fn add(self, rhs: Vec3) -> Self::Output {
        Self(
            self.0 + rhs.x(),
            self.1 + rhs.y(),
            self.2 + rhs.z(),
        )
    }
}

impl AddAssign<Vec3> for P3d {
    fn add_assign(&mut self, rhs: Vec3) {
        self.0 += rhs.x();
        self.1 += rhs.y();
        self.2 += rhs.z();
    }
}

impl Add<P3d> for Vec3 {
    type Output = P3d;
    fn add(self, rhs: P3d) -> Self::Output {
        P3d(
            self.x() + rhs.0,
            self.y() + rhs.1,
            self.z() + rhs.2,
        )
    }
}

impl Sub for P3d {
    type Output = Vec3;
    fn sub(self, rhs: Self) -> Self::Output {
        Vec3::new(
            self.0 - rhs.0,
            self.1 - rhs.1,
            self.2 - rhs.2,
        )
    }
}

impl Sub<Vec3> for P3d {
    type Output = P3d;
    fn sub(self, rhs: Vec3) -> Self::Output {
        P3d(
            self.0 - rhs.x(),
            self.1 - rhs.y(),
            self.2 - rhs.z(),
        )
    }
}

impl SubAssign<Vec3> for P3d {
    fn sub_assign(&mut self, rhs: Vec3) {
        self.0 -= rhs.x();
        self.1 -= rhs.y();
        self.2 -= rhs.z();
    }
}
