pub mod sphere;
pub mod moving_sphere;
pub mod aarectangle;

pub mod prelude {
    pub use super::HitRecord;
    pub use super::Hittable;
    pub use super::HittableList;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::material::prelude::*;

#[derive(Clone)]
pub struct HitRecord {
   pub p: P3d,
   pub normal: Vec3,
   pub t: f64,
   pub u: f64,
   pub v: f64,
   pub material: Rc<dyn Material>,
   pub front_face: bool,
}

impl HitRecord {
    pub fn new(p: P3d, normal: Vec3, t: f64, u: f64, v: f64, material: Rc<dyn Material>, ray: &Ray) -> Self {
        let mut rec = Self { p, normal, t, u, v, material, front_face: false };
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
    fn bounding_box(&self, t0: f64, t1: f64) -> Option<AABB>;
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
        let mut rec = None;
        let mut closest = t_max;

        for hittable in &self.hittables {
            if let Some(subrec) = hittable.hit(ray, t_min, closest) {
                closest = subrec.t;
                rec = Some(subrec);
            }
        }

        rec
    }

    fn bounding_box(&self, t0: f64, t1: f64) -> Option<AABB> {
        if self.hittables.is_empty() {
            None
        } else {
            self.hittables
                .iter()
                .fold(
                    self.hittables[0].bounding_box(t0, t1),
                    |bounding_box, hittable| match bounding_box {
                        Some(ref original_box) => match hittable.bounding_box(t0, t1) {
                            Some(ref new_box) => Some(AABB::surrounding_box(original_box, new_box)),
                            None => None,
                        },
                        None => None,
                    }
                )
        }
    }
}
