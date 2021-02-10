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
use texture::checker_texture::CheckerTexture;

fn random_scene(rng: &mut SmallRng) -> HittableList {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(RGB::new(0.2, 0.3, 0.1), RGB::new(0.9, 0.9, 0.9)));
    hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(Lambertian::with_texture(checker.clone()))));

    // let material_ground = Lambertian::with_color(RGB::new(0.5, 0.5, 0.5));
    // hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(material_ground)));

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
                    hittables.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, Rc::new(sphere_material)));
                } else if which_material < 0.95 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0, 0.5);
                    let sphere_material = Metal::new(albedo, fuzz);
                    hittables.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                } else {
                    // glass
                    let sphere_material = Dielectric::new(1.5);
                    hittables.push(Sphere::new(center, 0.2, Rc::new(sphere_material)));
                }
            }
        }
    }

    let material1 = Dielectric::new(1.5);
    hittables.push(Sphere::new(P3d::new( 0.0, 1.0, 0.0), 1.0, Rc::new(material1)));

    let material2 = Lambertian::with_color(RGB::new(0.4, 0.2, 0.1));
    hittables.push(Sphere::new(P3d::new(-4.0, 1.0, 0.0), 1.0, Rc::new(material2)));

    let material3 = Metal::new(RGB::new(0.7, 0.6, 0.5), 0.0);
    hittables.push(Sphere::new(P3d::new( 4.0, 1.0, 0.0), 1.0, Rc::new(material3)));

    hittables
}

fn two_spheres() -> HittableList {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(RGB::new(0.2, 0.3, 0.1), RGB::new(0.9, 0.9, 0.9)));
    hittables.push(Sphere::new(P3d::new(0.0, -10.0, 0.0), 10.0, Rc::new(Lambertian::with_texture(checker.clone()))));
    hittables.push(Sphere::new(P3d::new(0.0,  10.0, 0.0), 10.0, Rc::new(Lambertian::with_texture(checker.clone()))));


    hittables
}

fn main() {
    let mut rng = SmallRng::from_entropy();

    // Image
    let aspect_ratio = ASPECT_RATIO;
    let image_width = IMAGE_WIDTH;
    let samples_per_pixel = SAMPLES_PER_PIXEL;
    let vertical_field_of_view;

    // Camera
    let lookfrom;
    let lookat;
    let mut aperture = 0.0;

    // Scene
    let scene;

    match 0 {
        1 => {
            scene                   = random_scene(&mut rng);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            aperture                = 0.1;
        },
        _ => {
            scene                   = two_spheres();
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
        }
    }

    let image_height = (image_width as f64 / aspect_ratio) as i32;

    let bvh = BVHNode::new(scene, 0.0, 1.0, &mut rng);

    let viewup  = Vec3::new( 0.0, 1.0, 0.0);
    let focus_distance = 10.0;
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
