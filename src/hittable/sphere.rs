use crate::utilities::*;
use crate::ray::Ray;
use crate::hittable::*;

#[derive(Clone)]
pub struct Sphere {
    center: P3d,
    radius: f64,
    material: Rc<dyn Material>,
}

impl Sphere {
    pub fn new(center: P3d, radius: f64, material: Rc<dyn Material>) -> Self {
        Self { center, radius, material }
    }
}

impl Hittable for Sphere {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let oc = ray.origin() - self.center;
        let a = ray.direction().length2();
        let half_b = Vec3::dot(&oc, &ray.direction());
        let c = oc.length2() - self.radius * self.radius;
        let discriminant = half_b * half_b - a * c;

        if discriminant > 0.0 {
            let root = discriminant.sqrt();

            let t = (-half_b - root) / a;
            if t_min < t && t < t_max {
                let ray_at = ray.at(t);
                let mut rec = HitRecord::new(ray_at, (ray_at - self.center) / self.radius, t, self.material.clone());
                rec.set_face_normal(&ray);
                return Some(rec);
            }

            let t = (-half_b + root) / a;
            if t_min < t && t < t_max {
                let ray_at = ray.at(t);
                let mut rec = HitRecord::new(ray_at, (ray_at - self.center) / self.radius, t, self.material.clone());
                rec.set_face_normal(&ray);
                return Some(rec);
            }
        }

        None
    }
}
