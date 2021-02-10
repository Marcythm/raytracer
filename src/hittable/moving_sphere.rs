use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Clone)]
pub struct MovingSphere {
    pub center0  : P3d,
    pub center1  : P3d,
    pub time0    : f64,
    pub time1    : f64,
    pub radius   : f64,
    pub material : Rc<dyn Material>,
}

impl MovingSphere {
    pub fn new(center0: P3d, center1: P3d, time0: f64, time1: f64, radius: f64, material: Rc<dyn Material>) -> Self {
        Self { center0, center1, time0, time1, radius, material }
    }

    pub fn center(&self, time: f64) -> P3d {
        self.center0 + ((time - self.time0) / (self.time1 - self.time0)) * (self.center1 - self.center0)
    }
}

impl Hittable for MovingSphere {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let oc = ray.origin - self.center(ray.time);
        let a = ray.direction.length2();
        let half_b = Vec3::dot(oc, ray.direction);
        let c = oc.length2() - self.radius * self.radius;
        let discriminant = half_b * half_b - a * c;

        if discriminant > 0.0 {
            let root = discriminant.sqrt();

            let t = (-half_b - root) / a;
            if t_min < t && t < t_max {
                let p = ray.at(t);
                let normal = (p - self.center(ray.time)) / self.radius;
                return Some(HitRecord::new(p, normal, t, self.material.clone(), ray));
            }

            let t = (-half_b + root) / a;
            if t_min < t && t < t_max {
                let p = ray.at(t);
                let normal = (p - self.center(ray.time)) / self.radius;
                return Some(HitRecord::new(p, normal, t, self.material.clone(), ray));
            }
        }

        None
    }

    fn bounding_box(&self, t0: f64, t1: f64) -> Option<AABB> {
        Some(AABB::surrounding_box(
            &AABB::new(
                self.center(t0) - Vec3::new(self.radius, self.radius, self.radius),
                self.center(t0) + Vec3::new(self.radius, self.radius, self.radius),
            ),
            &AABB::new(
                self.center(t1) - Vec3::new(self.radius, self.radius, self.radius),
                self.center(t1) + Vec3::new(self.radius, self.radius, self.radius),
            )
        ))
    }
}
