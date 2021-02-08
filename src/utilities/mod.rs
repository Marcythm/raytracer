pub mod p3d;
pub mod vec3;
pub mod rgb;

pub use p3d::P3d;
pub use vec3::Vec3;
pub use rgb::RGB;

pub const INFINITY: f64 = 1e15;
pub use std::f64::consts::PI;

pub fn deg2rad(deg: f64) -> f64 {
    deg * PI / 180.0
}
