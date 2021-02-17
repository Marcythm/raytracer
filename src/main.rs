#![feature(destructuring_assignment)]
pub mod utilities;

pub mod ray;
pub mod camera;
pub mod aabb;
pub mod bvhnode;
pub mod instance;

pub mod hittable;
pub mod material;
pub mod texture;
pub mod transform;
pub mod medium;
pub mod pdf;

pub mod prelude;
pub mod scene;

use prelude::*;

use image::{ImageBuffer, RgbImage};
use indicatif::ProgressBar;

fn main() {
    let mut rng = SmallRng::from_entropy();

    // Image
    let mut aspect_ratio            = ASPECT_RATIO;
    let mut image_width             = IMAGE_WIDTH;
    let mut samples_per_pixel       = SAMPLES_PER_PIXEL;
    let vertical_field_of_view;
    let background;

    // Camera
    let lookfrom;
    let lookat;
    let mut aperture = 0.0;

    // Scene
    let scene;
    let mut lights = Rc::new(HittableList::default()) as Rc<dyn Hittable>;

    match 0 {
        1 => {
            scene                   = scene::random_scene(&mut rng);
            background              = RGB::new(  0.7, 0.8, 1.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            aperture                = 0.1;
        },
        // 2 => {
        //     scene                   = scene::two_spheres();
        //     background              = RGB::new(  0.7, 0.8, 1.0);
        //     lookfrom                = P3d::new( 13.0, 2.0, 3.0);
        //     lookat                  = P3d::new(  0.0, 0.0, 0.0);
        //     vertical_field_of_view  = 20.0;
        // },
        // 3 => {
        //     scene                   = scene::two_perlin_spheres();
        //     background              = RGB::new(  0.7, 0.8, 1.0);
        //     lookfrom                = P3d::new( 13.0, 2.0, 3.0);
        //     lookat                  = P3d::new(  0.0, 0.0, 0.0);
        //     vertical_field_of_view  = 20.0;
        // },
        // 4 => {
        //     scene                   = scene::earth();
        //     background              = RGB::new(  0.7, 0.8, 1.0);
        //     lookfrom                = P3d::new( 13.0, 2.0, 3.0);
        //     lookat                  = P3d::new(  0.0, 0.0, 0.0);
        //     vertical_field_of_view  = 20.0;
        // },
        // 5 => {
        //     scene                   = scene::simple_light();
        //     samples_per_pixel       = 400;
        //     background              = RGB::new(  0.0, 0.0, 0.0);
        //     lookfrom                = P3d::new( 26.0, 3.0, 6.0);
        //     lookat                  = P3d::new(  0.0, 2.0, 0.0);
        //     vertical_field_of_view  = 20.0;
        // },
        6 => {
            (scene, lights)         = scene::cornell_box();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 10;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 278.0, 278.0, -800.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
        7 => {
            scene                   = scene::cornell_smoke();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 200;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 278.0, 278.0, -800.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
        8 => {
            scene                   = scene::final_scene(&mut rng);
            aspect_ratio            = 1.0;
            image_width             = 800;
            samples_per_pixel       = 10000;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 478.0, 278.0, -600.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
        _ => {
            (scene, lights)         = scene::night(&mut rng);
            aspect_ratio            = 3.0 / 2.0;
            image_width             = 1600;
            samples_per_pixel       = 1000;
            background              = RGB::new(  0.0, 0.0, 0.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            aperture                = 0.1;
        }
    }

    let image_height = (image_width as f64 / aspect_ratio) as u32;

    let viewup  = Vec3::new( 0.0, 1.0, 0.0);
    let focus_distance = 10.0;
    let camera = Camera::new(
        lookfrom, lookat, viewup,
        vertical_field_of_view, aspect_ratio,
        aperture, focus_distance,
        0.0, 1.0
    );

    // Render
    let mut image: RgbImage = ImageBuffer::new(image_width, image_height);
    let indicator = ProgressBar::new(image_height as u64);

    for j in 0..image_height {
        for i in 0..image_width {
            let mut pixel_color = RGB::new(0.0, 0.0, 0.0);
            for _ in 0..samples_per_pixel {
                let u = (i as f64 + rng.gen_range(0.0..1.0)) / (image_width - 1) as f64;
                let v = (j as f64 + rng.gen_range(0.0..1.0)) / (image_height - 1) as f64;
                pixel_color += camera.get_ray(u, v, &mut rng).color(scene.clone(), background, lights.clone(), MAX_DEPTH, &mut rng);
            }
            image.put_pixel(
                i,
                image_height - j - 1,
                image::Rgb(RGB::into(pixel_color / samples_per_pixel as f64))
            );
        }
        indicator.inc(1);
    }

    image.save("image.png").unwrap();
    indicator.finish();

    // // Render
    // println!("P3");
    // println!("{} {}", image_width, image_height);
    // println!("255");

    // for j in (0..image_height).rev() {
    //     eprintln!("Rendering: {} lines remaining", j);
    //     for i in 0..image_width {
    //         let mut pixel_color = RGB::new(0.0, 0.0, 0.0);
    //         for _ in 0..samples_per_pixel {
    //             let u = (i as f64 + rng.gen_range(0.0..1.0)) / (image_width - 1) as f64;
    //             let v = (j as f64 + rng.gen_range(0.0..1.0)) / (image_height - 1) as f64;
    //             pixel_color += camera.get_ray(u, v, &mut rng).color(&scene, background, lights.clone(), MAX_DEPTH, &mut rng);
    //         }
    //         println!("{}", pixel_color / samples_per_pixel as f64);
    //     }
    // }
    // eprintln!("\nDone.");
}
