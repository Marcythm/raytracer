use crate::utilities::prelude::*;
use crate::transform::prelude::*;

#[derive(Clone)]
pub struct RotationX { // Rotation around X-axis
    pub sin_theta: f64,
    pub cos_theta: f64,
}

impl RotationX {
    pub fn new(angle: f64) -> Self {
        Self {
            sin_theta: angle.to_radians().sin(),
            cos_theta: angle.to_radians().cos(),
        }
    }

    pub fn set_angle(&mut self, angle: f64) {
        self.sin_theta = angle.to_radians().sin();
        self.cos_theta = angle.to_radians().cos();
    }
}

impl Transform for RotationX {
    fn transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            p.x,
            self.cos_theta * p.y - self.sin_theta * p.z,
            self.sin_theta * p.y + self.cos_theta * p.z,
        )
    }

    fn inverse_transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            p.x,
            self.sin_theta * p.z + self.cos_theta * p.y,
            self.cos_theta * p.z - self.sin_theta * p.y,
        )
    }

    fn transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            v.x,
            self.cos_theta * v.y - self.sin_theta * v.z,
            self.sin_theta * v.y + self.cos_theta * v.z,
        )
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            v.x,
            self.sin_theta * v.z + self.cos_theta * v.y,
            self.cos_theta * v.z - self.sin_theta * v.y,
        )
    }
}

#[derive(Clone)]
pub struct RotationY { // Rotation around Y-axis
    pub sin_theta: f64,
    pub cos_theta: f64,
}

impl RotationY {
    pub fn new(angle: f64) -> Self {
        Self {
            sin_theta: angle.to_radians().sin(),
            cos_theta: angle.to_radians().cos(),
        }
    }

    pub fn set_angle(&mut self, angle: f64) {
        self.sin_theta = angle.to_radians().sin();
        self.cos_theta = angle.to_radians().cos();
    }
}

impl Transform for RotationY {
    fn transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            self.sin_theta * p.z + self.cos_theta * p.x,
            p.y,
            self.cos_theta * p.z - self.sin_theta * p.x,
        )
    }

    fn inverse_transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            self.cos_theta * p.x - self.sin_theta * p.z,
            p.y,
            self.sin_theta * p.x + self.cos_theta * p.z,
        )
    }

    fn transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            self.sin_theta * v.z + self.cos_theta * v.x,
            v.y,
            self.cos_theta * v.z - self.sin_theta * v.x,
        )
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            self.cos_theta * v.x - self.sin_theta * v.z,
            v.y,
            self.sin_theta * v.x + self.cos_theta * v.z,
        )
    }
}

#[derive(Clone)]
pub struct RotationZ { // Rotation around Z-axis
    pub sin_theta: f64,
    pub cos_theta: f64,
}

impl RotationZ {
    pub fn new(angle: f64) -> Self {
        Self {
            sin_theta: angle.to_radians().sin(),
            cos_theta: angle.to_radians().cos(),
        }
    }

    pub fn set_angle(&mut self, angle: f64) {
        self.sin_theta = angle.to_radians().sin();
        self.cos_theta = angle.to_radians().cos();
    }
}

impl Transform for RotationZ {
    fn transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            self.cos_theta * p.x - self.sin_theta * p.y,
            self.sin_theta * p.x + self.cos_theta * p.y,
            p.z,
        )
    }

    fn inverse_transform_point(&self, p: P3d) -> P3d {
        P3d::new(
            self.sin_theta * p.y + self.cos_theta * p.x,
            self.cos_theta * p.y - self.sin_theta * p.x,
            p.z,
        )
    }

    fn transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            self.cos_theta * v.x - self.sin_theta * v.y,
            self.sin_theta * v.x + self.cos_theta * v.y,
            v.z,
        )
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        Vec3::new(
            self.sin_theta * v.y + self.cos_theta * v.x,
            self.cos_theta * v.y - self.sin_theta * v.x,
            v.z,
        )
    }
}
