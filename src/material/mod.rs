pub mod metal;
pub mod lambertian;

pub use metal::Metal;
pub use lambertian::Lambertian;

use crate::utilities::*;
use crate::ray::Ray;
use crate::hittable::*;

pub trait Material {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)>;
}
