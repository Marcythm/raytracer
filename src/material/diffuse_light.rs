use crate::utilities::prelude::*;
use crate::material::prelude::*;
use crate::texture::prelude::*;
use crate::texture::constant_texture::ConstantTexture;

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
}

impl Material for DiffuseLight {
    fn emitted(&self, u: f64, v: f64, p: P3d) -> RGB {
        self.emit.value(u, v, p)
    }
}
