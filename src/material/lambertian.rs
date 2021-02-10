use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;
use crate::texture::prelude::*;
use crate::texture::solid_color::SolidColor;

#[derive(Clone)]
pub struct Lambertian {
    pub albedo: Rc<dyn Texture>,
}

impl Lambertian {
    pub fn with_texture(albedo: Rc<dyn Texture>) -> Self {
        Self { albedo }
    }

    pub fn with_color(albedo: RGB) -> Self {
        Self { albedo: Rc::new(SolidColor::with_color(albedo)) }
    }

    pub fn with_rgb(r: f64, g: f64, b: f64) -> Self {
        Self { albedo: Rc::new(SolidColor::with_rgb(r, g, b)) }
    }
}

impl Material for Lambertian {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)> {
        Some((
            Ray::new(rec.p, rec.normal + Vec3::random_unit_vector(rng), ray.time),
            self.albedo.value(rec.u, rec.v, rec.p),
        ))
    }
}
