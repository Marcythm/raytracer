pub mod lambertian;
pub mod metal;

pub mod prelude {
    pub use super::lambertian::Lambertian;
    pub use super::metal::Metal;
    pub use super::Material;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;

pub trait Material {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)>;
}
