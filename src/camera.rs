use crate::utilities::prelude::*;
use crate::ray::Ray;

#[derive(Debug, Clone, Copy, Default)]
pub struct Camera {
    pub origin            : P3d,
    pub horizontal        : Vec3,
    pub vertical          : Vec3,
    pub lower_left_corner : P3d,
    pub u                 : Vec3,
    pub v                 : Vec3,
    pub w                 : Vec3,
    pub lens_radius       : f64,
}

impl Camera {
    pub fn new(
        lookfrom: P3d, lookat: P3d, viewup: Vec3,
        vertical_field_of_view: f64, aspect_ratio: f64,
        aperture: f64, focus_distance: f64
    ) -> Self {
        let theta = deg2rad(vertical_field_of_view);
        let h = (theta / 2.0).tan();
        let viewport_height = 2.0 * h;
        let viewport_width = aspect_ratio * viewport_height;

        let w = -(lookat - lookfrom).unit();
        let u = Vec3::cross(viewup, w).unit();
        let v = Vec3::cross(w, u);

        let origin = lookfrom;
        let horizontal = focus_distance * viewport_width * u;
        let vertical = focus_distance * viewport_height * v;
        Self {
            origin,
            horizontal,
            vertical,
            lower_left_corner: origin - horizontal / 2.0 - vertical / 2.0 - focus_distance * w,
            u,
            v,
            w,
            lens_radius: aperture / 2.0
        }
    }

    pub fn get_ray(&self, w: f64, h: f64, rng: &mut SmallRng) -> Ray {
        let rd = self.lens_radius * Vec3::random_in_unit_disk(rng);
        let offset = rd.x * self.u + rd.y * self.v;
        Ray::from_to(self.origin + offset, self.lower_left_corner + w * self.horizontal + h * self.vertical)
    }
}
