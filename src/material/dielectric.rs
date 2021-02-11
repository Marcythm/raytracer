use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

pub fn schlick(cosine: f64, refractive_index: f64) -> f64 {
    // a polynomial approximation by Schlick
    let r0 = ((1.0 - refractive_index) / (1.0 + refractive_index)).powi(2);
    r0 + (1.0 - r0) * (1.0 - cosine).powi(5)
}

#[derive(Clone)]
pub struct Dielectric {
    pub refractive_index: f64,
}

impl Dielectric {
    pub fn new(refractive_index: f64) -> Dielectric {
        Self { refractive_index }
    }

}

impl Material for Dielectric {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)> {
        let unit_direction = ray.direction.unit();
        let cos_theta = Vec3::dot(-unit_direction, rec.normal).min(1.0);
        let sin_theta = (1.0 - cos_theta * cos_theta).sqrt();
        let etai_over_etat = if rec.front_face { 1.0 / self.refractive_index } else { self.refractive_index };

        if etai_over_etat * sin_theta > 1.0 || rng.gen_range(0.0, 1.0) < schlick(cos_theta, etai_over_etat) {
            Some((Ray::new(rec.p, unit_direction.reflect_on(rec.normal), 0.0), RGB::new(1.0 , 1.0, 1.0)))
        } else {
            Some((Ray::new(rec.p, unit_direction.refract_on(rec.normal, etai_over_etat), 0.0), RGB::new(1.0, 1.0, 1.0)))
        }
    }
}
