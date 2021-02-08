use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Dielectric {
    refractive_index: f64,
}

impl Dielectric {
    pub fn new(refractive_index: f64) -> Dielectric {
        Self { refractive_index }
    }
}

impl Material for Dielectric {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, _: &mut SmallRng) -> Option<(Ray, RGB)> {
        let unit_direction = ray.direction().unit();
        let etai_over_etat = if rec.front_face { 1.0 / self.refractive_index } else { self.refractive_index };

        Some((Ray::new(rec.p, unit_direction.refract_on(rec.normal, etai_over_etat)), RGB::new(1.0, 1.0, 1.0)))
    }
}
