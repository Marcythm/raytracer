pub mod sphere;

pub mod prelude {
    pub use super::HitRecord;
    pub use super::Hittable;
    pub use super::HittableList;

    pub use super::sphere::Sphere;
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
    pub fn new(p: P3d, normal: Vec3, t: f64, material: Rc<dyn Material>) -> Self {
        Self { p, normal, t, material, front_face: false }
    }

    pub fn set_face_normal(&mut self, ray: &Ray) {
        self.front_face = Vec3::dot(ray.direction(), self.normal) < 0.0;
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
    objects: Vec<Rc<dyn Hittable>>,
}

impl HittableList {
    pub fn clear(&mut self) {
        self.objects.clear();
    }

    pub fn push<T: Hittable + 'static>(&mut self, object: T) {
        self.objects.push(Rc::new(object));
    }
    pub fn push_ptr<T: Hittable + 'static>(&mut self, ptr: Rc<T>) {
        self.objects.push(ptr);
    }
}

impl Hittable for HittableList {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let mut sol = None;
        let mut closest = t_max;

        for object in &self.objects {
            if let Some(subsol) = object.hit(&ray, t_min, closest) {
                closest = subsol.t;
                sol = Some(subsol);
            }
        }

        sol
    }
}
