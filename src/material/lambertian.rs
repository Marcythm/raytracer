use super::super::{
    utilities::prelude::*,
    ray::Ray,
    hittable::prelude::*,
    material::prelude::*,
    texture::{
        prelude::*,
        constant_texture::ConstantTexture,
    },
    pdf::cosine_pdf::CosinePDF,
};

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
    fn scatter(&self, _: &Ray, rec: &HitRecord, _: &mut SmallRng) -> Option<ScatterRecord> {
        Some(ScatterRecord::Diffuse{
            pdf: Rc::new(CosinePDF::new(rec.normal)),
            attenuation: self.albedo.value(rec.u, rec.v, rec.p),
        })
    }

    fn scattering_pdf(&self, _: &Ray, rec: &HitRecord, scattered: &Ray) -> f64 {
        let cosine = rec.normal.dot(scattered.direction.unit());
        if cosine < 0.0 { 0.0 } else { cosine / PI }
    }
}
