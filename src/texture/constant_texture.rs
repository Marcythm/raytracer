use crate::utilities::prelude::*;
use crate::texture::prelude::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct ConstantTexture {
    pub color: RGB,
}

impl ConstantTexture {
    pub fn with_color(color: RGB) -> Self {
        Self { color }
    }

    pub fn with_rgb(r: f64, g: f64, b: f64) -> Self {
        Self { color: RGB { r, g, b } }
    }
}

impl Texture for ConstantTexture {
    fn value(&self, _: f64, _: f64, _: P3d) -> RGB {
        self.color
    }
}
