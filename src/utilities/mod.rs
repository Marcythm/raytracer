pub mod p3d;
pub mod vec3;
pub mod onb;
pub mod rgb;

pub mod prelude {
    pub use super::{
        p3d::P3d,
        vec3::Vec3,
        rgb::RGB,
        onb::ONB,
    };

    pub use rand::{Rng, rngs::SmallRng, SeedableRng};
    pub use std::rc::Rc;
    pub use std::cell::RefCell;

    // Image
    #[cfg(feature = "high-quality")]
    pub const ASPECT_RATIO      : f64 = 3.0 / 2.0;
    #[cfg(feature = "high-quality")]
    pub const IMAGE_WIDTH       : u32 = 1200;
    #[cfg(feature = "high-quality")]
    pub const SAMPLES_PER_PIXEL : u32 = 500;

    #[cfg(not(feature = "high-quality"))]
    pub const ASPECT_RATIO      : f64 = 16.0 / 9.0;
    #[cfg(not(feature = "high-quality"))]
    pub const IMAGE_WIDTH       : u32 = 400;
    #[cfg(not(feature = "high-quality"))]
    pub const SAMPLES_PER_PIXEL : u32 = 100;

    pub const IMAGE_HEIGHT      : u32 = (IMAGE_WIDTH as f64 / ASPECT_RATIO) as u32;
    pub const GAMMA             : f64 = 2.0;

    // Camera
    pub const VIEWPORT_HEIGHT   : f64 = 2.0;
    pub const VIEWPORT_WIDTH    : f64 = ASPECT_RATIO * VIEWPORT_HEIGHT;
    pub const FOCAL_LENGTH      : f64 = 1.0;
    pub const MAX_DEPTH         : u32 = 50;

    // Constants
    pub const INFINITY          : f64 = 1e15;
    pub const EPS               : f64 = 1e-5;
    pub use std::f64::consts::PI;

    pub fn deg2rad(deg: f64) -> f64 {
        deg * PI / 180.0
    }
}
