pub mod utilities;

pub mod ray;
pub mod camera;
pub mod aabb;
pub mod bvhnode;

pub mod hittable;
pub mod material;
pub mod texture;

use utilities::prelude::*;
use camera::Camera;
use bvhnode::BVHNode;

use hittable::prelude::*;
use hittable::sphere::Sphere;
use hittable::moving_sphere::MovingSphere;

// use material::prelude::*;
use material::lambertian::Lambertian;
use material::metal::Metal;
use material::dielectric::Dielectric;

// use texture::prelude::*;


fn random_scene(rng: &mut SmallRng) -> HittableList {
    let mut scene = HittableList::default();

    let material_ground = Lambertian::with_color(RGB::new(0.5, 0.5, 0.5));
    scene.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(material_ground)));

    for a in -11..11 {
        for b in -11..11 {
            let center = P3d::new(a as f64 + 0.9 * rng.gen_range(0.0, 1.0), 0.2, b as f64 + 0.9 * rng.gen_range(0.0, 1.0));

            if (center - P3d::new(4.0, 0.2, 0.0)).length() > 0.9 {
                let which_material = rng.gen_range(0.0, 1.0);

                if which_material < 0.8 {
                    // diffuse
                    let albedo = RGB::random(0.0, 1.0, rng) * RGB::random(0.0, 1.0, rng);
                    let sphere_material = Lambertian::with_color(albedo);
                    let center1 = center + Vec3::new(0.0, rng.gen_range(0.0, 0.5), 0.0);
                    scene.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, Rc::new(sphere_material)));
                } else if which_material < 0.95 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0, 0.5);
                    let sphere_material = Metal::new(albedo, fuzz);
                    scene.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                } else {
                    // glass
                    let sphere_material = Dielectric::new(1.5);
                    scene.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                }
            }
        }
    }

    let material1 = Dielectric::new(1.5);
    scene.push(Sphere::new(P3d::new( 0.0, 1.0, 0.0), 1.0, Rc::new(material1)));

    let material2 = Lambertian::with_color(RGB::new(0.4, 0.2, 0.1));
    scene.push(Sphere::new(P3d::new(-4.0, 1.0, 0.0), 1.0, Rc::new(material2)));

    let material3 = Metal::new(RGB::new(0.7, 0.6, 0.5), 0.0);
    scene.push(Sphere::new(P3d::new( 4.0, 1.0, 0.0), 1.0, Rc::new(material3)));

    scene
}

fn main() {
    let mut rng = SmallRng::from_entropy();

    // Image
    let mut aspect_ratio = ASPECT_RATIO;
    let mut image_width = IMAGE_WIDTH;
    let mut samples_per_pixel = SAMPLES_PER_PIXEL;
    let mut vertical_field_of_view = 20.0;

    let image_height = (image_width as f64 / aspect_ratio) as i32;

    // Scene
    let scene = random_scene(&mut rng);
    let bvh = BVHNode::new(scene, 0.0, 1.0, &mut rng);

    // Camera
    let lookfrom = P3d::new( 13.0, 2.0, 3.0);
    let lookat   = P3d::new(  0.0, 0.0, 0.0);
    let viewup  = Vec3::new( 0.0, 1.0, 0.0);
    let focus_distance = 10.0;
    let aperture = 0.1;
    let camera = Camera::new(
        lookfrom, lookat, viewup,
        vertical_field_of_view, aspect_ratio,
        aperture, focus_distance,
        0.0, 1.0
    );

    // Render
    println!("P3");
    println!("{} {}", image_width, image_height);
    println!("255");

    for j in (0..image_height).rev() {
        eprintln!("Rendering: {} lines remaining", j);
        for i in 0..image_width {
            let mut pixel_color = RGB::new(0.0, 0.0, 0.0);
            for _ in 0..samples_per_pixel {
                let u = (i as f64 + rng.gen_range(0.0, 1.0)) / (image_width - 1) as f64;
                let v = (j as f64 + rng.gen_range(0.0, 1.0)) / (image_height - 1) as f64;
                pixel_color += camera.get_ray(u, v, &mut rng).color(&bvh, MAX_DEPTH, &mut rng);
            }
            println!("{}", pixel_color / samples_per_pixel as f64);
        }
    }
    eprintln!("\nDone.");
}
