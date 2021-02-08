pub mod utilities;
pub mod ray;
pub mod camera;
pub mod hittable;
pub mod material;

use utilities::prelude::*;
use hittable::prelude::*;
use material::prelude::*;
use camera::Camera;

fn main() {
    // World
    let material_ground = Rc::new(Lambertian::new(RGB::new(0.8, 0.8, 0.0)));
    let material_center = Rc::new(Dielectric::new(1.5));
    let material_left = Rc::new(Dielectric::new(1.5));
    let material_right = Rc::new(Metal::new(RGB::new(0.8, 0.6, 0.2), 1.0));

    let mut world = HittableList::default();
    world.push(Sphere::new(P3d::new(0.0, -100.5, -1.0), 100.0, material_ground.clone()));
    world.push(Sphere::new(P3d::new(0.0, 0.0, -1.0), 0.5, material_center.clone()));
    world.push(Sphere::new(P3d::new(-1.0, 0.0, -1.0), 0.5, material_left.clone()));
    world.push(Sphere::new(P3d::new(-1.0, 0.0, -1.0), -0.4, material_left.clone()));
    world.push(Sphere::new(P3d::new(1.0, 0.0, -1.0), 0.5, material_right.clone()));

    // world.push(Sphere::new(P3d::new(0.0, 0.0, -1.0), 0.5));
    // world.push(Sphere::new(P3d::new(0.0, -100.5, -1.0), 100.0));

    // Camera
    let camera = Camera::new();
    let mut rng = SmallRng::from_entropy();

    // Render
    println!("P3");
    println!("{} {}", IMAGE_WIDTH, IMAGE_HEIGHT);
    println!("255");

    for j in (0..IMAGE_HEIGHT).rev() {
        eprintln!("Rendering: {} lines remaining", j);
        for i in 0..IMAGE_WIDTH {
            let mut pixel_color = RGB::new(0.0, 0.0, 0.0);
            for _ in 0..SAMPLES_PER_PIXEL {
                let u = (i as f64 + rng.gen_range(0.0, 1.0)) / (IMAGE_WIDTH - 1) as f64;
                let v = (j as f64 + rng.gen_range(0.0, 1.0)) / (IMAGE_HEIGHT - 1) as f64;
                pixel_color += camera.get_ray(u, v).color(&world, MAX_DEPTH, &mut rng);
            }
            println!("{}", pixel_color);
        }
    }
    eprintln!("\nDone.");
}
