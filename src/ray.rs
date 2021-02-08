pub use crate::utilities::{p3d::P3d, vec3::Vec3, rgb::RGB};

#[derive(Debug, Clone, Copy, Default)]
pub struct Ray {
    origin: P3d,
    direction: Vec3,
}

impl Ray {
    pub fn new(origin: P3d, direction: Vec3) -> Self {
        Self { origin, direction }
    }
    pub fn between(origin: P3d, destination: P3d) -> Self {
        Self { origin, direction: destination - origin }
    }

    pub fn origin(&self) -> P3d {
        self.origin
    }
    pub fn direction(&self) -> Vec3 {
        self.direction
    }

    pub fn at(&self, t: f64) -> P3d {
        self.origin + t * self.direction
    }

    pub fn color(&self) -> RGB {
        if self.hit_sphere(P3d::new(0.0, 0.0, -1.0), 0.5) {
            RGB::new(1.0, 0.0, 0.0)
        } else {
            let t = 0.5 * (self.direction.unit().y() + 1.0);
            (1.0 - t) * RGB::new(1.0, 1.0, 1.0) + t * RGB::new(0.5, 0.7, 1.0)
        }
    }

    pub fn hit_sphere(&self, center: P3d, radius: f64) -> bool {
        let oc = self.origin - center;
        let a = Vec3::dot(&self.direction, &self.direction);
        let b = 2.0 * Vec3::dot(&oc, &self.direction);
        let c = oc.length2() - radius * radius;
        let discriminant = b * b - 4.0 * a * c;
        discriminant > 0.0
    }
}
