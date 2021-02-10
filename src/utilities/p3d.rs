use std::ops::{Add, AddAssign, Sub, SubAssign};

use crate::utilities::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct P3d {
    pub x: f64,
    pub y: f64,
    pub z: f64,
}

impl P3d {
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self { x, y, z }
    }
}

impl Add<Vec3> for P3d {
    type Output = Self;
    fn add(self, rhs: Vec3) -> Self::Output {
        Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
        }
    }
}

impl AddAssign<Vec3> for P3d {
    fn add_assign(&mut self, rhs: Vec3) {
        self.x += rhs.x;
        self.y += rhs.y;
        self.z += rhs.z;
    }
}

impl Add<P3d> for Vec3 {
    type Output = P3d;
    fn add(self, rhs: P3d) -> Self::Output {
        P3d {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
        }
    }
}

impl Sub for P3d {
    type Output = Vec3;
    fn sub(self, rhs: Self) -> Self::Output {
        Vec3::new(
            self.x - rhs.x,
            self.y - rhs.y,
            self.z - rhs.z,
        )
    }
}

impl Sub<Vec3> for P3d {
    type Output = P3d;
    fn sub(self, rhs: Vec3) -> Self::Output {
        P3d {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
            z: self.z - rhs.z,
        }
    }
}

impl SubAssign<Vec3> for P3d {
    fn sub_assign(&mut self, rhs: Vec3) {
        self.x -= rhs.x;
        self.y -= rhs.y;
        self.z -= rhs.z;
    }
}
