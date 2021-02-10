use crate::utilities::prelude::*;
use crate::texture::prelude::*;
use crate::texture::solid_color::SolidColor;

#[derive(Clone)]
pub struct CheckerTexture {
    pub even : Rc<dyn Texture>,
    pub odd  : Rc<dyn Texture>,
}

impl CheckerTexture {
    pub fn with_texture(texture0: Rc<dyn Texture>, texture1: Rc<dyn Texture>) -> Self {
        Self {
            even : texture0,
            odd  : texture1
        }
    }

    pub fn with_color(color0: RGB, color1: RGB) -> Self {
        Self {
            even : Rc::new(SolidColor::with_color(color0)),
            odd  : Rc::new(SolidColor::with_color(color1)),
        }
    }
}

impl Texture for CheckerTexture {
    fn value(&self, u: f64, v: f64, p: P3d) -> RGB {
        if (10.0 * p.x).sin() * (10.0 * p.y).sin() * (10.0 * p.z).sin() < 0.0 {
            self.odd.value(u, v, p)
        } else {
            self.even.value(u, v, p)
        }
    }
}
