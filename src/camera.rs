use crate::utilities::prelude::*;
use crate::ray::Ray;

#[derive(Debug, Clone, Copy, Default)]
pub struct Camera {
    origin: P3d,
    horizontal: Vec3,
    vertical: Vec3,
    lower_left_corner: P3d,
}

impl Camera {
    pub fn new(
        lookfrom: P3d, lookat: P3d, viewup: Vec3,
        vertical_field_of_view: f64, aspect_ratio: f64
    ) -> Self {
        let theta = deg2rad(vertical_field_of_view);
        let h = (theta / 2.0).tan();
        let viewport_height = 2.0 * h;
        let viewport_width = aspect_ratio * viewport_height;

        let w = -(lookat - lookfrom).unit();
        let u = Vec3::cross(viewup, w).unit();
        let v = Vec3::cross(w, u);

        let origin = lookfrom;
        let horizontal = viewport_width * u;
        let vertical = viewport_height * v;
        Self {
            origin,
            horizontal,
            vertical,
            lower_left_corner: origin - horizontal / 2.0 - vertical / 2.0 - w
        }
    }

    pub fn get_ray(&self, u: f64, v: f64) -> Ray {
        Ray::from_to(self.origin, self.lower_left_corner + u * self.horizontal + v * self.vertical)
    }
}
