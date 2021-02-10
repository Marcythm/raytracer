pub mod lambertian;
pub mod metal;
pub mod dielectric;
pub mod diffuse_light;
pub mod isotropic;

pub mod prelude {
    pub use super::Material;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;

pub trait Material {
    fn emitted(&self, _: f64, _: f64, _: P3d) -> RGB {
        RGB::new(0.0, 0.0, 0.0)
    }
    fn scatter(&self, _: &Ray, _: &HitRecord, _: &mut SmallRng) -> Option<(Ray, RGB)> {
        None
    }
}
