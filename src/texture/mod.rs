pub mod solid_color;

pub mod prelude {
    pub use super::Texture;
}

use crate::utilities::prelude::*;

pub trait Texture {
    fn value(&self, u: f64, v: f64, p: P3d) -> RGB;
}
