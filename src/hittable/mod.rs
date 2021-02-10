pub mod sphere;

pub mod prelude {
    pub use super::HitRecord;
    pub use super::Hittable;
    pub use super::HittableList;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::material::prelude::*;

#[derive(Clone)]
pub struct HitRecord {
   pub p: P3d,
   pub normal: Vec3,
   pub t: f64,
   pub material: Rc<dyn Material>,
   pub front_face: bool,
}

impl HitRecord {
    pub fn new(p: P3d, normal: Vec3, t: f64, material: Rc<dyn Material>, ray: &Ray) -> Self {
        let mut rec = Self { p, normal, t, material, front_face: false };
        rec.set_face_normal(ray);
        rec
    }

    pub fn set_face_normal(&mut self, ray: &Ray) {
        self.front_face = Vec3::dot(ray.direction, self.normal) < 0.0;
        if !self.front_face {
            self.normal = -self.normal;
        }
    }
}

pub trait Hittable {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord>;
}

#[derive(Clone, Default)]
pub struct HittableList {
    pub hittables: Vec<Rc<dyn Hittable>>,
}

impl HittableList {
    pub fn clear(&mut self) {
        self.hittables.clear();
    }

    pub fn push<T: Hittable + 'static>(&mut self, hittable: T) {
        self.hittables.push(Rc::new(hittable));
    }
    pub fn push_ptr<T: Hittable + 'static>(&mut self, ptr: Rc<T>) {
        self.hittables.push(ptr);
    }
}

impl Hittable for HittableList {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let mut sol = None;
        let mut closest = t_max;

        for hittable in &self.hittables {
            if let Some(subsol) = hittable.hit(&ray, t_min, closest) {
                closest = subsol.t;
                sol = Some(subsol);
            }
        }

        sol
    }
}
