pub mod lambertian;
pub mod metal;
pub mod dielectric;

pub mod prelude {
    pub use super::Material;

    pub use super::lambertian::Lambertian;
    pub use super::metal::Metal;
    pub use super::dielectric::Dielectric;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;

pub trait Material {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)>;
}
