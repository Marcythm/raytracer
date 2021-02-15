use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;
use crate::material::prelude::*;
use crate::texture::prelude::*;
use crate::texture::constant_texture::ConstantTexture;

#[derive(Clone)]
pub struct Lambertian {
    pub albedo: Rc<dyn Texture>,
}

impl Lambertian {
    pub fn with_texture(albedo: Rc<dyn Texture>) -> Self {
        Self { albedo }
    }

    pub fn with_color(albedo: RGB) -> Self {
        Self { albedo: Rc::new(ConstantTexture::with_color(albedo)) }
    }

    pub fn with_rgb(r: f64, g: f64, b: f64) -> Self {
        Self { albedo: Rc::new(ConstantTexture::with_rgb(r, g, b)) }
    }
}

impl Material for Lambertian {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB, f64)> {
        let basis = ONB::build_from(rec.normal);
        let direction = basis.transform(Vec3::random_cosine_direction(rng)).unit();
        Some((
            Ray::new(rec.p, direction, ray.time),
            self.albedo.value(rec.u, rec.v, rec.p),
            basis.w.dot(direction) / PI,
        ))
    }

    fn scattering_pdf(&self, _: &Ray, rec: &HitRecord, scattered: &Ray) -> f64 {
        let cosine = rec.normal.dot(scattered.direction.unit());
        if cosine < 0.0 { 0.0 } else { cosine / PI }
    }
}
