use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Clone)]
pub struct Sphere {
    pub center   : P3d,
    pub radius   : f64,
    pub material : Rc<dyn Material>,
}

impl Sphere {
    pub fn new(center: P3d, radius: f64, material: Rc<dyn Material>) -> Self {
        Self { center, radius, material }
    }

    pub fn get_sphere_uv(normal: Vec3) -> (f64, f64) {
        let phi = normal.z.atan2(normal.x);
        let theta = normal.y.asin();
        (1.0 - (phi + PI) / (2.0 * PI), (theta + PI / 2.0) / PI)
    }
}

impl Hittable for Sphere {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let oc = ray.origin - self.center;
        let a = ray.direction.length2();
        let half_b = oc.dot(ray.direction);
        let c = oc.length2() - self.radius * self.radius;
        let discriminant = half_b * half_b - a * c;

        if discriminant > 0.0 {
            let root = discriminant.sqrt();

            let t = (-half_b - root) / a;
            if t_min < t && t < t_max {
                let p = ray.at(t);
                let normal = (p - self.center) / self.radius;
                let (u, v) = Self::get_sphere_uv(normal);
                return Some(HitRecord::new(p, normal, t, u, v, self.material.clone(), ray));
            }

            let t = (-half_b + root) / a;
            if t_min < t && t < t_max {
                let p = ray.at(t);
                let normal = (p - self.center) / self.radius;
                let (u, v) = Self::get_sphere_uv(normal);
                return Some(HitRecord::new(p, normal, t, u, v, self.material.clone(), ray));
            }
        }

        None
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(AABB::new(
            self.center - Vec3::new(self.radius, self.radius, self.radius),
            self.center + Vec3::new(self.radius, self.radius, self.radius),
        ))
    }

    fn pdf_value(&self, origin: P3d, direction: Vec3) -> f64 {
        if let Some(_) = self.hit(&Ray::new(origin, direction, 0.0), EPS, INFINITY) {
            let cos_theta_max = (1.0 - self.radius.powi(2) / (self.center - origin).length2()).sqrt();
            let solid_angle = 2.0 * PI * (1.0 - cos_theta_max);

            1.0 / solid_angle
        } else {
            0.0
        }
    }

    fn random(&self, origin: P3d, rng: &mut SmallRng) -> Vec3 {
        let direction = self.center - origin;
        ONB::build_from(direction)
        .transform(Vec3::random_to_sphere(self.radius, direction.length2(), rng))
    }
}
