use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Lambertian {
    albedo: RGB,
}

impl Lambertian {
    pub fn new(albedo: RGB) -> Lambertian {
        Self { albedo }
    }
}

impl Material for Lambertian {
    fn scatter(&self, _: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)> {
        Some((Ray::new(rec.p, rec.normal + Vec3::random_unit_vector(rng)), self.albedo))
    }
}
