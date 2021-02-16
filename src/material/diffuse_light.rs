use super::super::{
    utilities::prelude::*,
    ray::Ray,
    hittable::prelude::*,
    material::prelude::*,
    texture::{
        prelude::*,
        constant_texture::ConstantTexture,
    },
};

#[derive(Clone)]
pub struct DiffuseLight {
    pub emit: Rc<dyn Texture>,
}

impl DiffuseLight {
    pub fn with_texture(emit: Rc<dyn Texture>) -> Self {
        Self { emit }
    }

    pub fn with_color(color: RGB) -> Self {
        Self { emit: Rc::new(ConstantTexture::with_color(color)) }
    }

    pub fn with_rgb(r: f64, g: f64, b: f64) -> Self {
        Self { emit: Rc::new(ConstantTexture::with_rgb(r, g, b)) }
    }
}

impl Material for DiffuseLight {
    fn emitted(&self, _: &Ray, _: &HitRecord, u: f64, v: f64, p: P3d) -> RGB {
        self.emit.value(u, v, p)
    }
}
