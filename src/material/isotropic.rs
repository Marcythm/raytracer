use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;
use crate::texture::prelude::*;
use crate::texture::constant_texture::ConstantTexture;

#[derive(Clone)]
pub struct Isotropic {
    pub albedo: Rc<dyn Texture>,
}

impl Isotropic {
    pub fn with_texture(texture: Rc<dyn Texture>) -> Self {
        Self { albedo: texture }
    }

    pub fn with_color(color: RGB) -> Self {
        Self { albedo: Rc::new(ConstantTexture::with_color(color)) }
    }
}

impl Material for Isotropic {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB, f64)> {
        Some((
            Ray::new(rec.p, Vec3::random_in_unit_sphere(rng), ray.time),
            self.albedo.value(rec.u, rec.v, rec.p),
            0.0,
        ))
    }
}
