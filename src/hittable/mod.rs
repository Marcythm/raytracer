pub mod sphere;
pub mod hittablelist;

pub use hittablelist::HittableList;
pub use sphere::Sphere;

use crate::utilities::*;
use crate::ray::Ray;
use crate::material::*;

#[derive(Clone)]
pub struct HitRecord {
   pub p: P3d,
   pub normal: Vec3,
   pub t: f64,
   pub material: Rc<dyn Material>,
   pub front_face: bool,
}

impl HitRecord {
    pub fn new(p: P3d, normal: Vec3, t: f64, material: Rc<dyn Material>) -> Self {
        Self { p, normal, t, material, front_face: false }
    }

    pub fn set_face_normal(&mut self, ray: &Ray) {
        self.front_face = Vec3::dot(&ray.direction(), &self.normal) < 0.0;
        if !self.front_face {
            self.normal = -self.normal;
        }
    }
}

pub trait Hittable {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord>;
}
