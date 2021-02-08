pub mod metal;

pub use metal::Metal;

use crate::utilities::*;
use crate::ray::Ray;
use crate::hittable::HitRecord;

pub trait Material {
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<(Ray, RGB)>;
}
