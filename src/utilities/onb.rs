use crate::utilities::vec3::Vec3;

/// Orthonormal Basis
#[derive(Clone)]
pub struct ONB {
    pub u: Vec3,
    pub v: Vec3,
    pub w: Vec3,
}

impl ONB {
    pub fn build_from(normal: Vec3) -> Self {
        let w = normal.unit();
        let v = w.cross(
            if w.x.abs() > 0.9 {
                Vec3::new(0.0, 1.0, 0.0)
            } else {
                Vec3::new(1.0, 0.0, 0.0)
            }
        ).unit();

        Self {
            u: w.cross(v),
            v,
            w,
        }
    }

    pub fn location(&self, x: f64, y: f64, z: f64) -> Vec3 {
        x * self.u + y * self.v + z * self.w
    }

    pub fn transform(&self, vec: Vec3) -> Vec3 {
        vec.x * self.u + vec.y * self.v + vec.z * self.w
    }
}
