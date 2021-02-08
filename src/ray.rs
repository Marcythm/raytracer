pub use crate::utilities::{p3d::P3d, vec3::Vec3, rgb::RGB};

#[derive(Debug, Clone, Copy, Default)]
pub struct Ray {
    origin: P3d,
    direction: Vec3,
}

impl Ray {
    fn new(origin: P3d, direction: Vec3) -> Self {
        Self { origin, direction }
    }

    fn origin(&self) -> P3d {
        self.origin
    }
    fn direction(&self) -> Vec3 {
        self.direction
    }

    fn at(&self, t: f64) -> P3d {
        self.origin + t * self.direction
    }
}
