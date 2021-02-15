use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Clone)]
pub struct Metal {
    pub albedo : RGB,
    pub fuzz   : f64,
}

impl Metal {
    pub fn new(albedo: RGB, fuzz: f64) -> Metal {
        Self { albedo, fuzz }
    }
}

impl Material for Metal {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB, f64)> {
        let reflected = ray.direction.unit().reflect_on(rec.normal) + self.fuzz * Vec3::random_in_unit_sphere(rng);
        if reflected.dot(rec.normal) > 0.0 {
            Some((Ray::new(rec.p, reflected, 0.0), self.albedo, 0.0))
        } else {
            None
        }
    }
}
