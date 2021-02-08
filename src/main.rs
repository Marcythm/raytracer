pub mod utilities;
pub mod ray;
pub mod camera;
pub mod hittable;
pub mod material;

use utilities::prelude::*;
use hittable::prelude::*;
use material::prelude::*;
use camera::Camera;

fn random_scene(rng: &mut SmallRng) -> HittableList {
    let mut world = HittableList::default();

    let material_ground = Lambertian::new(RGB::new(0.5, 0.5, 0.5));
    world.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(material_ground)));

    for a in -11..11 {
        for b in -11..11 {
            let center = P3d::new(a as f64 + 0.9 * rng.gen_range(0.0, 1.0), 0.2, b as f64 + 0.9 * rng.gen_range(0.0, 1.0));

            if (center - P3d::new(4.0, 0.2, 0.0)).length() > 0.9 {
                let which_material = rng.gen_range(0.0, 1.0);

                if which_material < 0.8 {
                    // diffuse
                    let albedo = RGB::random(0.0, 1.0, rng) * RGB::random(0.0, 1.0, rng);
                    let sphere_material = Lambertian::new(albedo);
                    world.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                } else if which_material < 0.95 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0, 0.5);
                    let sphere_material = Metal::new(albedo, fuzz);
                    world.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                } else {
                    // glass
                    let sphere_material = Dielectric::new(1.5);
                    world.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                }
            }
        }
    }

    let material1 = Dielectric::new(1.5);
    world.push(Sphere::new(P3d::new(0.0, 1.0, 0.0), 1.0, Rc::new(material1)));

    let material2 = Lambertian::new(RGB::new(0.4, 0.2, 0.1));
    world.push(Sphere::new(P3d::new(-4.0, 1.0, 0.0), 1.0, Rc::new(material2)));

    let material3 = Metal::new(RGB::new(0.7, 0.6, 0.5), 0.0);
    world.push(Sphere::new(P3d::new(4.0, 1.0, 0.0), 1.0, Rc::new(material3)));

    world
}

fn main() {
    let mut rng = SmallRng::from_entropy();

    // World
    let world = random_scene(&mut rng);

    // Camera
    let lookfrom = P3d::new(13.0, 2.0, 3.0);
    let lookat = P3d::new(0.0, 0.0,0.0);
    let viewup = Vec3::new(0.0, 1.0, 0.0);
    let focus_distance = 10.0;
    let aperture = 0.1;
    let camera = Camera::new(
        lookfrom, lookat, viewup,
        20.0, ASPECT_RATIO,
        aperture, focus_distance
    );

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
                pixel_color += camera.get_ray(u, v, &mut rng).color(&world, MAX_DEPTH, &mut rng);
            }
            println!("{}", pixel_color);
        }
    }
    eprintln!("\nDone.");
}
