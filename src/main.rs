pub mod utilities;
pub mod ray;

use utilities::{p3d::P3d, vec3::Vec3, rgb::RGB};
use ray::Ray;

// Image
const ASPECT_RATIO: f64 = 16.0 / 9.0;
const IMAGE_WIDTH : i32 = 256;
const IMAGE_HEIGHT: i32 = 256;

// Camera
const VIEWPORT_HEIGHT: f64 = 2.0;
const VIEWPORT_WIDTH : f64 = ASPECT_RATIO * VIEWPORT_HEIGHT;
const FOCAL_LENGTH   : f64 = 1.0;

fn main() {
    // Camera
    let origin = P3d::new(0.0, 0.0, 0.0);
    let horizontal = Vec3::new(VIEWPORT_WIDTH, 0.0, 0.0);
    let vertical = Vec3::new(0.0, VIEWPORT_HEIGHT, 0.0);
    let lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3::new(0.0, 0.0, FOCAL_LENGTH);

    // Render
    println!("P3");
    println!("{} {}", IMAGE_WIDTH, IMAGE_HEIGHT);
    println!("255");

    for j in (0..IMAGE_HEIGHT).rev() {
        eprintln!("Rendering: {} lines remaining", j);
        for i in 0..IMAGE_WIDTH {
            let u = i as f64 / (IMAGE_WIDTH - 1) as f64;
            let v = j as f64 / (IMAGE_HEIGHT - 1) as f64;
            println!("{}", Ray::between(origin, lower_left_corner + u * horizontal + v * vertical).color());
        }
    }
}
