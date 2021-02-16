use super::super::{
    utilities::prelude::*,
    ray::Ray,
    hittable::prelude::*,
    material::prelude::*,
};

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
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<ScatterRecord> {
        let reflected = ray.direction.unit().reflect_on(rec.normal) + self.fuzz * Vec3::random_in_unit_sphere(rng);
        Some(ScatterRecord::Specular {
            specular_ray: Ray::new(rec.p, reflected, 0.0),
            attenuation: self.albedo,
        })
    }
}
