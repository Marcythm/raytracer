pub mod p3d;
pub mod vec3;
pub mod rgb;

pub use p3d::P3d;
pub use vec3::Vec3;
pub use rgb::RGB;

pub use rand::{Rng, rngs::SmallRng, SeedableRng};


// Image
pub const ASPECT_RATIO      : f64 = 16.0 / 9.0;
pub const IMAGE_WIDTH       : i32 = 400;
pub const IMAGE_HEIGHT      : i32 = (IMAGE_WIDTH as f64 / ASPECT_RATIO) as i32;
pub const SAMPLES_PER_PIXEL : i32 = 100;

// Camera
pub const VIEWPORT_HEIGHT : f64 = 2.0;
pub const VIEWPORT_WIDTH  : f64 = ASPECT_RATIO * VIEWPORT_HEIGHT;
pub const FOCAL_LENGTH    : f64 = 1.0;
pub const MAX_DEPTH       : i32 = 50;

// Constants
pub const INFINITY: f64 = 1e15;
pub use std::f64::consts::PI;

pub fn deg2rad(deg: f64) -> f64 {
    deg * PI / 180.0
}

pub fn clamp(x: f64, min: f64, max: f64) -> f64 {
    x.max(min).min(max)
}
