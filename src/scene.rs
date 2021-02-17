use super::prelude::*;

/// final scene of Raytracing: In One Weekend
pub fn random_scene(rng: &mut SmallRng) -> Rc<dyn Hittable> {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(
        RGB::new(0.2, 0.3, 0.1),
        RGB::new(0.9, 0.9, 0.9)
    ));
    let checker_gound = Rc::new(Lambertian::with_texture(checker.clone()));
    hittables.push(Sphere::new(
        P3d::new(0.0, -1000.0, 0.0),
        1000.0,
        checker_gound.clone()
    ));

    // let material_ground = Lambertian::with_color(RGB::new(0.5, 0.5, 0.5));
    // hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(material_ground)));

    for a in -11..11 {
        for b in -11..11 {
            let center = P3d::new(
                a as f64 + 0.9 * rng.gen_range(0.0..1.0),
                0.2,
                b as f64 + 0.9 * rng.gen_range(0.0..1.0),
            );

            if (center - P3d::new(4.0, 0.2, 0.0)).length() > 0.9 {
                let which_material = rng.gen_range(0.0..1.0);

                if which_material < 0.8 {
                    // diffuse
                    let albedo = RGB::random(0.0, 1.0, rng) * RGB::random(0.0, 1.0, rng);
                    let sphere_material = Rc::new(Lambertian::with_color(albedo));
                    let center1 = center + Vec3::new(0.0, rng.gen_range(0.0..0.5), 0.0);
                    hittables.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, sphere_material.clone()));
                } else if which_material < 0.95 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0..0.5);
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
    hittables.push(Sphere::new(
        P3d::new( 0.0, 1.0, 0.0),
        1.0,
        material1.clone(),
    ));

    let material2 = Rc::new(Lambertian::with_color(RGB::new(0.4, 0.2, 0.1)));
    hittables.push(Sphere::new(
        P3d::new(-4.0, 1.0, 0.0),
        1.0,
        material2.clone(),
    ));

    let material3 = Rc::new(Metal::new(RGB::new(0.7, 0.6, 0.5), 0.0));
    hittables.push(Sphere::new(
        P3d::new( 4.0, 1.0, 0.0),
        1.0,
        material3.clone(),
    ));

    Rc::new(BVHNode::new(hittables, 0.0, 1.0, rng))
}

// pub fn two_spheres() -> Rc<dyn Hittable> {
//     let mut hittables = HittableList::default();

//     let checker = Rc::new(CheckerTexture::with_color(
//         RGB::new(0.2, 0.3, 0.1),
//         RGB::new(0.9, 0.9, 0.9),
//     ));
//     hittables.push(Sphere::new(
//         P3d::new(0.0, -10.0, 0.0),
//         10.0,
//         Rc::new(Lambertian::with_texture(checker.clone())),
//     ));
//     hittables.push(Sphere::new(
//         P3d::new(0.0,  10.0, 0.0),
//         10.0,
//         Rc::new(Lambertian::with_texture(checker.clone())),
//     ));

//     Rc::new(hittables)
// }

// pub fn two_perlin_spheres() -> Rc<dyn Hittable> {
//     let mut hittables = HittableList::default();

//     let pertext = Rc::new(NoiseTexture::new(4.0));
//     hittables.push(Sphere::new(
//         P3d::new(0.0, -1000.0, 0.0),
//         1000.0,
//         Rc::new(Lambertian::with_texture(pertext.clone())),
//     ));
//     hittables.push(Sphere::new(
//         P3d::new(0.0,     2.0, 0.0),
//         2.0,
//         Rc::new(Lambertian::with_texture(pertext.clone())),
//     ));

//     Rc::new(hittables)
// }

// pub fn earth() -> Rc<dyn Hittable> {
//     let hittables = HittableList::default();

//     Rc::new(hittables)
// }

// pub fn simple_light() -> Rc<dyn Hittable> {
//     let mut hittables = HittableList::default();

//     let pertext = Rc::new(NoiseTexture::new(4.0));
//     hittables.push(Sphere::new(
//         P3d::new(0.0, -1000.0, 0.0),
//         1000.0,
//         Rc::new(Lambertian::with_texture(pertext.clone())),
//     ));
//     hittables.push(Sphere::new(
//         P3d::new(0.0,     2.0, 0.0),
//         2.0,
//         Rc::new(Lambertian::with_texture(pertext.clone())),
//     ));

//     let difflight = Rc::new(DiffuseLight::with_rgb(4.0, 4.0, 4.0));
//     hittables.push(XYAARectangle::new(
//         3.0, 5.0,
//         1.0, 3.0,
//         -2.0,
//         difflight.clone(),
//     ));

//     Rc::new(hittables)
// }

/// A Simple Cornell Box
pub fn cornell_box() -> (Rc<dyn Hittable>, Rc<dyn Hittable>) {
    let mut hittables = HittableList::default();

    let red   = Rc::new(Lambertian::with_rgb(0.65, 0.05, 0.05));
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    let green = Rc::new(Lambertian::with_rgb(0.12, 0.45, 0.15));
    let light = Rc::new(DiffuseLight::with_rgb(15.0, 15.0, 15.0));

    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, green.clone()));
    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0,   red.clone()));
    hittables.push(Instance::new(
        Rc::new(ZXAARectangle::new(227.0, 332.0, 213.0, 343.0, 554.0, light.clone())),
        Rc::new(Flip::new()),
    ));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0, white.clone()));
    hittables.push(ZXAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));
    hittables.push(XYAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, white.clone()));

    // hittables.push(Cuboid::new(P3d::new(130.0, 0.0,  65.0), P3d::new(295.0, 165.0, 230.0), white.clone()));
    // hittables.push(Cuboid::new(P3d::new(265.0, 0.0, 295.0), P3d::new(430.0, 330.0, 460.0), white.clone()));

    let light_rec = Rc::new(ZXAARectangle::new(227.0, 332.0, 213.0, 343.0, 554.0, light.clone()));

    // let aluminum = Rc::new(Metal::new(RGB::new(0.8, 0.85, 0.88), 0.0));

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

    let glass = Rc::new(Dielectric::new(1.5));
    let glass_sphere = Rc::new(Sphere::new(P3d::new(190.0, 90.0, 190.0), 90.0, glass.clone()));
    hittables.push_ptr(glass_sphere.clone());

    // hittables.push(Instance::new(
    //     Rc::new(Instance::new(
    //         Rc::new(Cuboid::new(
    //             P3d::new(0.0, 0.0, 0.0),
    //             P3d::new(165.0, 165.0, 165.0),
    //             white.clone(),
    //         )),
    //         Rc::new(RotationY::new(-18.0)),
    //     )),
    //     Rc::new(Translation::new(Vec3::new(130.0, 0.0, 65.0))),
    // ));

    let mut lights = HittableList::default();
    lights.push_ptr(light_rec.clone());
    lights.push_ptr(glass_sphere.clone());

    (Rc::new(hittables), Rc::new(lights))
}

/// Cornell Box with Smoke
pub fn cornell_smoke() -> Rc<dyn Hittable> {
    let mut hittables = HittableList::default();

    let red   = Rc::new(Lambertian::with_rgb(0.65, 0.05, 0.05));
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    let green = Rc::new(Lambertian::with_rgb(0.12, 0.45, 0.15));
    let light = Rc::new(DiffuseLight::with_rgb(7.0, 7.0, 7.0));

    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0, 555.0, green.clone()));
    hittables.push(YZAARectangle::new(  0.0, 555.0,   0.0, 555.0,   0.0,   red.clone()));
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

    Rc::new(hittables)
}

/// final scene of Raytracing: The Next Week
pub fn final_scene(rng: &mut SmallRng) -> Rc<dyn Hittable> {
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
            let y1 = rng.gen_range(1.0..101.1);
            let z1 = z0 + w;

            boxes1.push(Cuboid::new(
                P3d::new(x0, y0, z0),
                P3d::new(x1, y1, z1),
                ground.clone(),
            ));
        }
    }

    let mut hittables = HittableList::default();

    let light = Rc::new(DiffuseLight::with_rgb(7.0, 7.0, 7.0));
    hittables.push(ZXAARectangle::new(
        147.0, 412.0,
        123.0, 423.0,
        554.0,
        light.clone(),
    ));

    let center0 = P3d::new(400.0, 400.0, 200.0);
    let center1 = center0 + Vec3::new(30.0, 0.0, 0.0);

    let moving_sphere_material = Rc::new(Lambertian::with_rgb(0.7, 0.3, 0.1));
    hittables.push(MovingSphere::new(
        center0, center1,
        0.0, 1.0,
        50.0,
        moving_sphere_material.clone()
    ));

    let dielectric = Rc::new(Dielectric::new(1.5));
    hittables.push(Sphere::new(
        P3d::new(260.0, 150.0,  45.0),
        50.0,
        dielectric.clone(),
    ));
    hittables.push(Sphere::new(
        P3d::new(  0.0, 150.0, 145.0),
        50.0,
        Rc::new(Metal::new(
            RGB::new(0.8, 0.8, 0.9),
            10.0,
        )),
    ));

    let boundary1 = Rc::new(Sphere::new(
        P3d::new(360.0, 150.0, 145.0),
        70.0,
        dielectric.clone(),
    ));
    hittables.push_ptr(boundary1.clone());
    hittables.push(ConstantMedium::with_color(
        boundary1.clone(),
        RGB::new(0.2, 0.4, 0.9),
        0.2,
    ));

    let boundary2 = Rc::new(Sphere::new(
        P3d::new(0.0, 0.0, 0.0),
        5000.0,
        dielectric.clone(),
    ));
    hittables.push_ptr(boundary2.clone());
    hittables.push(ConstantMedium::with_color(
        boundary2.clone(),
        RGB::new(1.0, 1.0, 1.0),
        0.0001,
    ));

    // earth

    let pertext = Rc::new(NoiseTexture::new(0.1));
    hittables.push(Sphere::new(
        P3d::new(220.0, 280.0, 300.0),
        80.0,
        Rc::new(Lambertian::with_texture(pertext.clone())),
    ));

    let mut boxes2 = HittableList::default();
    let white = Rc::new(Lambertian::with_rgb(0.73, 0.73, 0.73));
    const BOX_NUM: i32 = 1000;
    for _ in 0..BOX_NUM {
        boxes2.push(Sphere::new(
            P3d::random(0.0, 165.0, rng),
            10.0,
            white.clone(),
        ));
    }

    hittables.push(BVHNode::new(boxes1, 0.0, 1.0, rng));
    hittables.push(Instance::new(
        Rc::new(Instance::new(
            Rc::new(BVHNode::new(boxes2, 0.0, 1.0, rng)),
            Rc::new(RotationY::new(15.0)),
        )),
        Rc::new(Translation::new(Vec3::new(-100.0, 270.0, 395.0))),
    ));

    Rc::new(hittables)
}

pub fn night(rng: &mut SmallRng) -> (Rc<dyn Hittable>, Rc<dyn Hittable>) {
    let mut hittables = HittableList::default();

    let checker = Rc::new(CheckerTexture::with_color(
        RGB::new(0.2, 0.3, 0.1),
        RGB::new(0.9, 0.9, 0.9)
    ));
    let checker_gound = Rc::new(Lambertian::with_texture(checker.clone()));
    hittables.push(Sphere::new(
        P3d::new(0.0, -1000.0, 0.0),
        1000.0,
        checker_gound.clone()
    ));

    // let material_ground = Lambertian::with_color(RGB::new(0.5, 0.5, 0.5));
    // hittables.push(Sphere::new(P3d::new(0.0, -1000.0, 0.0), 1000.0, Rc::new(material_ground)));

    for a in -13..13 {
        for b in -13..13 {
            let radius = rng.gen_range(0.09..0.29);
            let center = P3d::new(
                a as f64 + 0.9 * rng.gen_range(0.0..1.0),
                radius,
                b as f64 + 0.9 * rng.gen_range(0.0..1.0),
            );

            if (center - P3d::new(4.0, 0.2, 0.0)).length() > 0.9 {
                let which_material = rng.gen_range(0.0..1.0);

                if which_material < 0.6 {
                    // diffuse light
                    let albedo = RGB::random(0.0, 1.0, rng) * RGB::random(0.0, 1.0, rng);
                    let sphere_material = Rc::new(DiffuseLight::with_color(albedo));
                    hittables.push(Sphere::new(center, radius, sphere_material.clone()));
                    // let center1 = center + Vec3::new(0.0, rng.gen_range(0.0..0.5), 0.0);
                    // hittables.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, sphere_material.clone()));
                } else if which_material < 0.65 {
                    // diffuse
                    let albedo = RGB::random(0.0, 1.0, rng) * RGB::random(0.0, 1.0, rng);
                    let sphere_material = Rc::new(Lambertian::with_color(albedo));
                    hittables.push(Sphere::new(center, radius, sphere_material.clone()));
                    // let center1 = center + Vec3::new(0.0, rng.gen_range(0.0..0.5), 0.0);
                    // hittables.push(MovingSphere::new(center, center1, 0.0, 1.0, 0.2, sphere_material.clone()));
                } else if which_material < 0.8 {
                    // metal
                    let albedo = RGB::random(0.5, 1.0, rng);
                    let fuzz = rng.gen_range(0.0..0.5);
                    let sphere_material = Rc::new(Metal::new(albedo, fuzz));
                    hittables.push(Sphere::new(center, radius, sphere_material.clone()));
                } else {
                    // glass
                    let sphere_material = Rc::new(Dielectric::new(1.5));
                    hittables.push(Sphere::new(center, radius, sphere_material.clone()));
                }
            }
        }
    }

    let material1 = Rc::new(Dielectric::new(4.0));
    hittables.push(Sphere::new(
        P3d::new( 3.0, 0.45, 0.0),
        0.45,
        material1.clone(),
    ));

    let material2 = Rc::new(DiffuseLight::with_texture(
        Rc::new(CheckerTexture::with_color(
            RGB::new(1.0, 1.0, 1.0),
            RGB::new(
                (12.0 * 16.0 + 7.8) / 255.0,
                (9.0 * 16.0 + 4.0) / 255.0,
                (160.0 + 4.0) / 255.0,
            ),
        )),
    ));
    hittables.push(Sphere::new(
        P3d::new(3.0, 0.45, 0.0),
        0.45 * (1.0 - EPS),
        material2.clone(),
    ));

    let light = Rc::new(DiffuseLight::with_rgb(15.0, 15.0, 15.0));
    let light_rec = Rc::new(ZXAARectangle::new(227.0, 332.0, 213.0, 343.0, 554.0, light.clone()));

    (
        Rc::new(BVHNode::new(hittables, 0.0, 1.0, rng)),
        light_rec,
    )
}
