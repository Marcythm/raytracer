use crate::utilities::*;
use crate::ray::Ray;

#[derive(Debug, Clone, Copy, Default)]
pub struct Camera {
    origin: P3d,
    horizontal: Vec3,
    vertical: Vec3,
    lower_left_corner: P3d,
}

impl Camera {
    pub fn new() -> Self {
        let origin = P3d::new(0.0, 0.0, 0.0);
        let horizontal = Vec3::new(VIEWPORT_WIDTH, 0.0, 0.0);
        let vertical = Vec3::new(0.0, VIEWPORT_HEIGHT, 0.0);
        Self {
            origin,
            horizontal,
            vertical,
            lower_left_corner: origin - horizontal / 2.0 - vertical / 2.0 - Vec3::new(0.0, 0.0, FOCAL_LENGTH)
        }
    }

    pub fn get_ray(&self, u: f64, v: f64) -> Ray {
        Ray::between(self.origin, self.lower_left_corner + u * self.horizontal + v * self.vertical)
    }
}
