pub mod utilities;

use utilities::{p3d::P3d, vec3::Vec3, rgb::RGB};

// Image
const IMAGE_WIDTH : i32 = 256;
const IMAGE_HEIGHT: i32 = 256;

fn main() {
    // Render
    println!("P3");
    println!("{} {}", IMAGE_WIDTH, IMAGE_HEIGHT);
    println!("255");


    for j in (0..IMAGE_HEIGHT).rev() {
        eprintln!("Rendering: {} lines remaining", j);
        for i in 0..IMAGE_WIDTH {
            println!("{}", RGB::new(
                i as f64 / (IMAGE_WIDTH - 1) as f64,
                j as f64 / (IMAGE_HEIGHT - 1) as f64,
                0.25
            ));
        }
    }
}
