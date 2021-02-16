pub mod cosine_pdf;
pub mod hittable_pdf;
pub mod mixture_pdf;

pub mod prelude {
    pub use super::PDF;
}

use crate::utilities::prelude::*;

pub trait PDF {
    fn value(&self, direction: Vec3) -> f64;
    fn generate(&self, rng: &mut SmallRng) -> Vec3;
}
