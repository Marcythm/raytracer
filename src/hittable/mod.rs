pub mod sphere;

use crate::utilities::{p3d::P3d, vec3::Vec3};
use crate::ray::Ray;

#[derive(Debug, Clone, Copy, Default)]
pub struct HitRecord {
   pub p: P3d,
   pub normal: Vec3,
   pub t: f64,
}

pub trait Hittable {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord>;
}
