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

use utilities::prelude::*;
use camera::Camera;
// use aabb::AABB;
use bvhnode::BVHNode;
use instance::Instance;

use hittable::prelude::*;
use hittable::sphere::Sphere;
use hittable::moving_sphere::MovingSphere;
use hittable::aarectangle::XYAARectangle;
use hittable::aarectangle::YZAARectangle;
use hittable::aarectangle::ZXAARectangle;
use hittable::cuboid::Cuboid;

// use material::prelude::*;
use material::lambertian::Lambertian;
use material::metal::Metal;
use material::dielectric::Dielectric;
use material::diffuse_light::DiffuseLight;
// use material::istropic::Istropic;

// use texture::prelude::*;
use texture::checker_texture::CheckerTexture;
use texture::noise_texture::NoiseTexture;

// use transform::prelude::*;
use transform::translation::Translation;
// use transform::rotation::RotationX;
use transform::rotation::RotationY;
// use transform::rotation::RotationZ;

// use medium::prelude::*;
use medium::constant_medium::ConstantMedium;

fn random_scene(rng: &mut SmallRng) -> HittableList {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(RGB::new(0.2, 0.3, 0.1), RGB::new(0.9, 0.9, 0.9)));
    let checker_gound = Rc::new(Lambertian::with_texture(checker.clone()));
    hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, checker_gound.clone()));

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
                    let sphere_material = Rc::new(Lambertian::with_color(albedo));
                    let center1 = center + Vec3::new(0.0, rng.gen_range(0.0, 0.5), 0.0);
                    hittables.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, sphere_material.clone()));
                } else if which_material < 0.95 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0, 0.5);
                    let sphere_material = Rc::new(Metal::new(albedo, fuzz));
                    hittables.push(Sphere::new(center, 0.2, sphere_material.clone()));
                } else {
                    // glass
                    let sphere_material = Rc::new(Dielectric::new(1.5));
                    hittables.push(Sphere::new(center, 0.2, sphere_material.clone()));
                }
            }
        }
    }

    let material1 = Rc::new(Dielectric::new(1.5));
    hittables.push(Sphere::new(P3d::new( 0.0, 1.0, 0.0), 1.0, material1.clone()));

    let material2 = Rc::new(Lambertian::with_color(RGB::new(0.4, 0.2, 0.1)));
    hittables.push(Sphere::new(P3d::new(-4.0, 1.0, 0.0), 1.0, material2.clone()));

    let material3 = Rc::new(Metal::new(RGB::new(0.7, 0.6, 0.5), 0.0));
    hittables.push(Sphere::new(P3d::new( 4.0, 1.0, 0.0), 1.0, material3.clone()));

    hittables
}

fn two_spheres() -> HittableList {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(RGB::new(0.2, 0.3, 0.1), RGB::new(0.9, 0.9, 0.9)));
    hittables.push(Sphere::new(P3d::new(0.0, -10.0, 0.0), 10.0, Rc::new(Lambertian::with_texture(checker.clone()))));
    hittables.push(Sphere::new(P3d::new(0.0,  10.0, 0.0), 10.0, Rc::new(Lambertian::with_texture(checker.clone()))));

    hittables
}

fn two_perlin_spheres() -> HittableList {
    let mut hittables = HittableList::default();

    let pertext = Rc::new(NoiseTexture::new(4.0));
    hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(Lambertian::with_texture(pertext.clone()))));
    hittables.push(Sphere::new(P3d::new(0.0,     2.0, 0.0),    2.0, Rc::new(Lambertian::with_texture(pertext.clone()))));

    hittables
}

fn earth() -> HittableList {
    let hittables = HittableList::default();

    hittables
}

fn simple_light() -> HittableList {
    let mut hittables = HittableList::default();

    let pertext = Rc::new(NoiseTexture::new(4.0));
    hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(Lambertian::with_texture(pertext.clone()))));
    hittables.push(Sphere::new(P3d::new(0.0,     2.0, 0.0),    2.0, Rc::new(Lambertian::with_texture(pertext.clone()))));

    let difflight = Rc::new(DiffuseLight::with_rgb(4.0, 4.0, 4.0));
    hittables.push(XYAARectangle::new(3.0, 5.0, 1.0, 3.0, -2.0, difflight.clone()));

    hittables
}

fn cornell_box() -> HittableList {
    let mut hittables = HittableList::default();

    let red   = Rc::new(Lambertian::with_rgb(0.65, 0.05, 0.05));
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    let green = Rc::new(Lambertian::with_rgb(0.12, 0.45, 0.15));
    let light = Rc::new(DiffuseLight::with_rgb(15.0, 15.0, 15.0));

    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, green.clone()));
    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0, red.clone()));
    hittables.push(ZXAARectangle::new(227.0, 332.0, 213.0, 343.0, 554.0, light.clone()));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0, white.clone()));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));
    hittables.push(XYAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));

    // hittables.push(Cuboid::new(P3d::new(130.0, 0.0,  65.0), P3d::new(295.0, 165.0, 230.0), white.clone()));
    // hittables.push(Cuboid::new(P3d::new(265.0, 0.0, 295.0), P3d::new(430.0, 330.0, 460.0), white.clone()));

    hittables.push(Instance::new(
        Rc::new(Instance::new(
            Rc::new(Cuboid::new(
                P3d::new(0.0, 0.0, 0.0),
                P3d::new(165.0, 330.0, 165.0),
                white.clone(),
            )),
            Rc::new(RotationY::new(15.0)),
        )),
        Rc::new(Translation::new(Vec3::new(265.0, 0.0, 295.0))),
    ));
    hittables.push(Instance::new(
        Rc::new(Instance::new(
            Rc::new(Cuboid::new(
                P3d::new(0.0, 0.0, 0.0),
                P3d::new(165.0, 165.0, 165.0),
                white.clone(),
            )),
            Rc::new(RotationY::new(-18.0)),
        )),
        Rc::new(Translation::new(Vec3::new(130.0, 0.0, 65.0))),
    ));

    hittables
}

fn cornell_smoke() -> HittableList {
    let mut hittables = HittableList::default();

    let red   = Rc::new(Lambertian::with_rgb(0.65, 0.05, 0.05));
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    let green = Rc::new(Lambertian::with_rgb(0.12, 0.45, 0.15));
    let light = Rc::new(DiffuseLight::with_rgb(7.0, 7.0, 7.0));

    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, green.clone()));
    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0, red.clone()));
    hittables.push(ZXAARectangle::new(127.0, 332.0, 113.0, 443.0, 554.0, light.clone()));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0, white.clone()));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));
    hittables.push(XYAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));

    // hittables.push(Cuboid::new(P3d::new(130.0, 0.0,  65.0), P3d::new(295.0, 165.0, 230.0), white.clone()));
    // hittables.push(Cuboid::new(P3d::new(265.0, 0.0, 295.0), P3d::new(430.0, 330.0, 460.0), white.clone()));

    hittables.push(ConstantMedium::with_color(
        Rc::new(Instance::new(
            Rc::new(Instance::new(
                Rc::new(Cuboid::new(
                    P3d::new(0.0, 0.0, 0.0),
                    P3d::new(165.0, 330.0, 165.0),
                    white.clone(),
                )),
                Rc::new(RotationY::new(15.0)),
            )),
            Rc::new(Translation::new(Vec3::new(265.0, 0.0, 295.0))),
        )),
        RGB::new(0.0, 0.0, 0.0),
        0.01,
    ));
    hittables.push(ConstantMedium::with_color(
        Rc::new(Instance::new(
            Rc::new(Instance::new(
                Rc::new(Cuboid::new(
                    P3d::new(0.0, 0.0, 0.0),
                    P3d::new(165.0, 165.0, 165.0),
                    white.clone(),
                )),
                Rc::new(RotationY::new(-18.0)),
            )),
            Rc::new(Translation::new(Vec3::new(130.0, 0.0, 65.0))),
         )),
         RGB::new(1.0, 1.0, 1.0),
         0.01,
    ));

    hittables
}

fn final_scene(rng: &mut SmallRng) -> HittableList {
    let mut boxes1 = HittableList::default();

    let ground = Rc::new(Lambertian::with_rgb(0.48, 0.83, 0.53));
    const BOXES_PER_SIDE: i32 = 20;
    for i in 0..BOXES_PER_SIDE {
        for j in 0..BOXES_PER_SIDE {
            let w = 100.0;
            let x0 = -1000.0 + i as f64 * w;
            let y0 = 0.0;
            let z0 = -1000.0 + j as f64 * w;

            let x1 = x0 + w;
            let y1 = rng.gen_range(1.0, 101.1);
            let z1 = z0 + w;

            boxes1.push(Cuboid::new(P3d::new(x0, y0, z0), P3d::new(x1, y1, z1), ground.clone()));
        }
    }

    let mut hittables = HittableList::default();

    let light = Rc::new(DiffuseLight::with_rgb(7.0, 7.0, 7.0));
    hittables.push(ZXAARectangle::new(147.0, 412.0, 123.0, 423.0, 554.0, light.clone()));

    let center0 = P3d::new(400.0, 400.0, 200.0);
    let center1 = center0 + Vec3::new(30.0, 0.0, 0.0);

    let moving_sphere_material = Rc::new(Lambertian::with_rgb(0.7, 0.3, 0.1));
    hittables.push(MovingSphere::new(center0, center1, 0.0, 1.0, 50.0, moving_sphere_material.clone()));

    let dielectric = Rc::new(Dielectric::new(1.5));
    hittables.push(Sphere::new(P3d::new(260.0, 150.0,  45.0), 50.0, dielectric.clone()));
    hittables.push(Sphere::new(P3d::new(  0.0, 150.0, 145.0), 50.0, Rc::new(Metal::new(RGB::new(0.8, 0.8, 0.9), 10.0))));

    let boundary1 = Rc::new(Sphere::new(P3d::new(360.0, 150.0, 145.0), 70.0, dielectric.clone()));
    hittables.push_ptr(boundary1.clone());
    hittables.push(ConstantMedium::with_color(boundary1, RGB::new(0.2, 0.4, 0.9), 0.2));

    let boundary2 = Rc::new(Sphere::new(P3d::new(0.0, 0.0, 0.0), 5000.0, dielectric.clone()));
    hittables.push_ptr(boundary2.clone());
    hittables.push(ConstantMedium::with_color(boundary2, RGB::new(1.0, 1.0, 1.0), 0.0001));

    // earth

    let pertext = Rc::new(NoiseTexture::new(0.1));
    hittables.push(Sphere::new(P3d::new(220.0, 280.0, 300.0), 80.0, Rc::new(Lambertian::with_texture(pertext.clone()))));

    let mut boxes2 = HittableList::default();
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    const BOX_NUM: i32 = 1000;
    for _ in 0..BOX_NUM {
        boxes2.push(Sphere::new(P3d::random(0.0, 165.0, rng), 10.0, white.clone()));
    }

    hittables.push(BVHNode::new(boxes1, 0.0, 1.0, rng));
    hittables.push(Instance::new(
        Rc::new(Instance::new(
            Rc::new(BVHNode::new(boxes2, 0.0, 1.0, rng)),
            Rc::new(RotationY::new(15.0)),
        )),
        Rc::new(Translation::new(Vec3::new(-100.0, 270.0, 395.0))),
    ));

    hittables
}

fn main() {
    let mut rng = SmallRng::from_entropy();

    // Image
    let mut aspect_ratio = ASPECT_RATIO;
    let mut image_width = IMAGE_WIDTH;
    let mut samples_per_pixel = SAMPLES_PER_PIXEL;
    let vertical_field_of_view;
    let background;

    // Camera
    let lookfrom;
    let lookat;
    let mut aperture = 0.0;

    // Scene
    let scene;

    match 0 {
        1 => {
            scene                   = random_scene(&mut rng);
            background              = RGB::new(  0.7, 0.8, 1.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            aperture                = 0.1;
        },
        2 => {
            scene                   = two_spheres();
            background              = RGB::new(  0.7, 0.8, 1.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
        },
        3 => {
            scene                   = two_perlin_spheres();
            background              = RGB::new(  0.7, 0.8, 1.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
        },
        4 => {
            scene                   = earth();
            background              = RGB::new(  0.7, 0.8, 1.0);
            lookfrom                = P3d::new( 13.0, 2.0, 3.0);
            lookat                  = P3d::new(  0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
        },
        5 => {
            scene                   = simple_light();
            samples_per_pixel       = 400;
            background              = RGB::new(  0.0, 0.0, 0.0);
            lookfrom                = P3d::new( 26.0, 3.0, 6.0);
            lookat                  = P3d::new(  0.0, 2.0, 0.0);
            vertical_field_of_view  = 20.0;
        },
        6 => {
            scene                   = cornell_box();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 200;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 278.0, 278.0, -800.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
        7 => {
            scene                   = cornell_smoke();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 200;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 278.0, 278.0, -800.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
        _ => {
            scene                   = final_scene(&mut rng);
            aspect_ratio            = 1.0;
            image_width             = 800;
            samples_per_pixel       = 10000;
            background              = RGB::new(   0.0,   0.0,    0.0);
            lookfrom                = P3d::new( 478.0, 278.0, -600.0);
            lookat                  = P3d::new( 278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
        },
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
                pixel_color += camera.get_ray(u, v, &mut rng).color(&bvh, background, MAX_DEPTH, &mut rng);
            }
            println!("{}", pixel_color / samples_per_pixel as f64);
        }
    }
    eprintln!("\nDone.");
}
