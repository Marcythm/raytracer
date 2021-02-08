use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Metal {
    albedo: RGB,
}

impl Metal {
    pub fn new(albedo: RGB) -> Metal {
        Self { albedo }
    }
}

impl Material for Metal {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, _: &mut SmallRng) -> Option<(Ray, RGB)> {
        let reflected = ray.direction().unit().reflect_on(&rec.normal);
        if Vec3::dot(&reflected, &rec.normal) > 0.0 {
            Some((Ray::new(rec.p, reflected), self.albedo))
        } else {
            None
        }
    }
}
