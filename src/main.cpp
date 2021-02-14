#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"
#include "camera.hpp"
#include "aabb.hpp"
#include "bvhnode.hpp"
#include "instance.hpp"

#include "hittable.hpp"
#include "sphere.hpp"
#include "moving_sphere.hpp"
#include "aarectangle.hpp"
#include "cuboid.hpp"

#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"
#include "diffuse_light.hpp"
#include "isotropic.hpp"

#include "texture.hpp"
#include "constant_texture.hpp"
#include "checker_texture.hpp"
#include "noise_texture.hpp"
#include "image_texture.hpp"

#include "transform.hpp"
#include "translation.hpp"
#include "rotation.hpp"
#include "flip.hpp"

#include "medium.hpp"
#include "constant_medium.hpp"

#include "pdf.hpp"
#include "cosine_pdf.hpp"
#include "hittable_pdf.hpp"
#include "mixture_pdf.hpp"

auto random_scene() -> HittableList {
    HittableList scene;

    // const auto ground_material = std::make_shared<Lambertian>(RGB(0.5, 0.5, 0.5));
    // scene.push(Sphere(p3d(0.0, -1000.0, 0.0), 1000.0, ground_material));

    const auto checker = std::make_shared<CheckerTexture>(RGB(0.2, 0.3, 0.1), RGB(0.9, 0.9, 0.9));
    scene.push(Sphere(p3d(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(checker)));

    for (i32 a = -11; a < 11; ++a)
        for (i32 b = -11; b < 11; ++b) {
            const p3d center(a + 0.9 * random_f64(), 0.2, b + 0.9 * random_f64());

            if ((center - p3d(4.0, 0.2, 0.0)).length() > 0.9) {
                const f64 which_material = random_f64();

                if (which_material < 0.8) {
                    // diffuse
                    const auto albedo = RGB::random() * RGB::random();
                    const auto sphere_material = std::make_shared<Lambertian>(albedo);
                    const auto center1 = center + Vec3(0.0, random_f64(0.0, 0.5), 0.0);
                    scene.push(MovingSphere(center, center1, 0.0, 1.0, 0.2, sphere_material));
                } else if (which_material < 0.95) {
                    // metal
                    const auto albedo = RGB::random(0.5, 1.0);
                    const auto fuzz = random_f64(0.0, 0.5);
                    const auto sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.push(Sphere(center, 0.2, sphere_material));
                } else {
                    // glass
                    const auto sphere_material = std::make_shared<Dielectric>(1.5);
                    scene.push(Sphere(center, 0.2, sphere_material));
                }
            }
        }

    const auto material1 = std::make_shared<Dielectric>(1.5);
    scene.push(Sphere(
        p3d(0.0, 1.0, 0.0),
        1.0,
        material1
    ));

    const auto material2 = std::make_shared<Lambertian>(RGB(0.4, 0.2, 0.1));
    scene.push(Sphere(
        p3d(-4.0, 1.0, 0.0),
        1.0,
        material2
    ));

    const auto material3 = std::make_shared<Metal>(RGB(0.7, 0.6, 0.5), 0.0);
    scene.push(Sphere(
        p3d(4.0, 1.0, 0.0),
        1.0,
        material3
    ));

    return scene;
}

auto two_spheres() -> HittableList {
    HittableList hittables;

    const auto checker = std::make_shared<CheckerTexture>(
        RGB(0.2, 0.3, 0.1),
        RGB(0.9, 0.9, 0.9)
    );
    hittables.push(Sphere(
        p3d(0.0, -10.0, 0.0),
        10.0,
        std::make_shared<Lambertian>(checker)
    ));
    hittables.push(Sphere(
        p3d(0.0,  10.0, 0.0),
        10.0,
        std::make_shared<Lambertian>(checker)
    ));

    return hittables;
}

auto two_perlin_spheres() -> HittableList {
    HittableList hittables;

    const auto pertext = std::make_shared<NoiseTexture>(4.0);
    hittables.push(Sphere(
        p3d(0.0, -1000.0, 0.0),
        1000.0,
        std::make_shared<Lambertian>(pertext)
    ));
    hittables.push(Sphere(
        p3d(0.0, 2.0, 0.0),
        2.0,
        std::make_shared<Lambertian>(pertext)
    ));

    return hittables;
}

auto earth() -> HittableList {
    HittableList hittables;

    const auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
    const auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    hittables.push(
        Sphere(p3d(0.0, 0.0, 0.0),
        2.0,
        earth_surface
    ));

    return hittables;
}

auto simple_light() -> HittableList {
    HittableList hittables;

    const auto pertext = std::make_shared<NoiseTexture>(4.0);
    hittables.push(Sphere(
        p3d(0.0, -1000.0, 0.0),
        1000.0,
        std::make_shared<Lambertian>(pertext)
    ));
    hittables.push(Sphere(
        p3d(0.0, 2.0, 0.0),
        2.0,
        std::make_shared<Lambertian>(pertext)
    ));

    const auto difflight = std::make_shared<DiffuseLight>(RGB(4.0, 4.0, 4.0));
    hittables.push(XYAARectangle(
        3.0, 5.0,
        1.0, 3.0,
        -2.0,
        difflight
    ));

    return hittables;
}

auto cornell_box() -> HittableList {
    HittableList hittables;

    const auto red   = std::make_shared<Lambertian>  (RGB( 0.65,  0.05,  0.05));
    const auto white = std::make_shared<Lambertian>  (RGB( 0.73,  0.73,  0.73));
    const auto green = std::make_shared<Lambertian>  (RGB( 0.12,  0.45,  0.15));
    const auto light = std::make_shared<DiffuseLight>(RGB(15.00, 15.00, 15.00));

    hittables.push(YZAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, green));
    hittables.push(YZAARectangle(  0.0, 555.0,   0.0, 555.0,   0.0,   red));
    hittables.push(std::make_shared<Instance>(
        std::make_shared<ZXAARectangle>(227.0, 332.0, 213.0, 343.0, 554.0, light),
        std::make_shared<Flip>()
    ));
    hittables.push(ZXAARectangle(  0.0, 555.0,   0.0, 555.0,   0.0, white));
    hittables.push(ZXAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, white));
    hittables.push(XYAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, white));

    const auto box1 = std::make_shared<Instance>(
        std::make_shared<Instance>(
            std::make_shared<Cuboid>(
                p3d(0.0, 0.0, 0.0),
                p3d(165.0, 330.0, 165.0),
                white
            ),
            std::make_shared<RotationY>(15.0)
        ),
        std::make_shared<Translation>(Vec3(265.0, 0.0, 295.0))
    );
    const auto box2 = std::make_shared<Instance>(
        std::make_shared<Instance>(
            std::make_shared<Cuboid>(
                p3d(0.0, 0.0, 0.0),
                p3d(165.0, 165.0, 165.0),
                white
            ),
            std::make_shared<RotationY>(-18.0)
        ),
        std::make_shared<Translation>(Vec3(130.0, 0.0, 65.0))
    );

    hittables.push(box1);
    hittables.push(box2);

    return hittables;
}

auto cornell_smoke() -> HittableList {
    HittableList hittables;

    const auto red   = std::make_shared<Lambertian>  (RGB(0.65, 0.05, 0.05));
    const auto white = std::make_shared<Lambertian>  (RGB(0.73, 0.73, 0.73));
    const auto green = std::make_shared<Lambertian>  (RGB(0.12, 0.45, 0.15));
    const auto light = std::make_shared<DiffuseLight>(RGB(7.00, 7.00, 7.00));

    hittables.push(YZAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, green));
    hittables.push(YZAARectangle(  0.0, 555.0,   0.0, 555.0,   0.0,   red));
    hittables.push(ZXAARectangle(127.0, 432.0, 113.0, 443.0, 554.0, light));
    hittables.push(ZXAARectangle(  0.0, 555.0,   0.0, 555.0,   0.0, white));
    hittables.push(ZXAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, white));
    hittables.push(XYAARectangle(  0.0, 555.0,   0.0, 555.0, 555.0, white));

    const auto box1 = std::make_shared<Instance>(
        std::make_shared<Instance>(
            std::make_shared<Cuboid>(
                p3d(0.0, 0.0, 0.0),
                p3d(165.0, 330.0, 165.0),
                white
            ),
            std::make_shared<RotationY>(15.0)
        ),
        std::make_shared<Translation>(Vec3(265.0, 0.0, 295.0))
    );
    const auto box2 = std::make_shared<Instance>(
        std::make_shared<Instance>(
            std::make_shared<Cuboid>(
                p3d(0.0, 0.0, 0.0),
                p3d(165.0, 165.0, 165.0),
                white
            ),
            std::make_shared<RotationY>(-18.0)
        ),
        std::make_shared<Translation>(Vec3(130.0, 0.0, 65.0))
    );

    hittables.push(ConstantMedium(box1, RGB(0.0, 0.0, 0.0), 0.01));
    hittables.push(ConstantMedium(box2, RGB(1.0, 1.0, 1.0), 0.01));

    return hittables;
}

auto final_scene() -> HittableList {
    HittableList boxes1;
    const auto ground = std::make_shared<Lambertian>(RGB(0.48, 0.83, 0.53));

    const i32 boxes_per_side = 20;
    for (i32 i = 0; i < boxes_per_side; ++i)
        for (i32 j = 0; j < boxes_per_side; ++j) {
            const f64 w = 100.0;
            const f64 x0 = -1000.0 + i * w;
            const f64 y0 = 0.0;
            const f64 z0 = -1000.0 + j * w;

            const f64 x1 = x0 + w;
            const f64 y1 = random_f64(1.0, 101.1);
            const f64 z1 = z0 + w;

            boxes1.push(Cuboid(
                p3d(x0, y0, z0),
                p3d(x1, y1, z1),
                ground
            ));
        }

    HittableList hittables;

    const auto light = std::make_shared<DiffuseLight>(RGB(7.0, 7.0, 7.0));
    hittables.push(ZXAARectangle(
        147.0, 412.0,
        123.0, 423.0,
        554.0,
        light
    ));

    const p3d center1(400.0, 400.0, 200.0);
    const p3d center2 = center1 + Vec3(30.0, 0.0, 0.0);

    const auto moving_sphere_material = std::make_shared<Lambertian>(RGB(0.7, 0.3, 0.1));
    hittables.push(MovingSphere(
        center1, center2,
        0.0, 1.0,
        50.0,
        moving_sphere_material
    ));

    hittables.push(Sphere(
        p3d(260.0, 150.0,  45.0),
        50.0,
        std::make_shared<Dielectric>(1.5)
    ));
    hittables.push(Sphere(
        p3d(  0.0, 150.0, 145.0),
        50.0,
        std::make_shared<Metal>(
            RGB(0.8, 0.8, 0.9),
            10.0
        )
    ));

    const auto boundary1 = std::make_shared<Sphere>(
        p3d(360.0, 150.0, 145.0),
        70.0,
        std::make_shared<Dielectric>(1.5)
    );
    hittables.push(boundary1);
    hittables.push(ConstantMedium(
        boundary1,
        RGB(0.2, 0.4, 0.9),
        0.2
    ));

    const auto boundary2 = std::make_shared<Sphere>(
        p3d(0.0, 0.0, 0.0),
        5000.0,
        std::make_shared<Dielectric>(1.5)
    );
    hittables.push(boundary2);
    hittables.push(ConstantMedium(
        boundary2,
        RGB(1.0, 1.0, 1.0),
        0.0001
    ));

    const auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
    const auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    hittables.push(Sphere(
        p3d(400.0, 200.0, 400.0),
        100.0,
        earth_surface
    ));

    const auto pertext = std::make_shared<NoiseTexture>(0.1);
    hittables.push(Sphere(
        p3d(220.0, 280.0, 300.0),
        80.0,
        std::make_shared<Lambertian>(pertext)
    ));

    HittableList boxes2;
    const auto white = std::make_shared<Lambertian>  (RGB(0.73, 0.73, 0.73));
    const i32 box_num = 1000;
    for (i32 i = 0; i < box_num; ++i)
        boxes2.push(Sphere(
            p3d::random(0.0, 165.0),
            10.0,
            white
        ));

    hittables.push(BVHNode(boxes1, 0.0, 1.0));
    hittables.push(
        std::make_shared<Instance>(
            std::make_shared<Instance>(
                std::make_shared<BVHNode>(boxes2, 0.0, 1.0),
                std::make_shared<RotationY>(15.0)
            ),
            std::make_shared<Translation>(Vec3(-100.0, 270.0, 395.0))
        )
    );

    return hittables;
}

auto main() -> i32 {
    // Image
    f64 aspect_ratio      = ASPECT_RATIO;
    i32 image_width       = IMAGE_WIDTH;
    i32 samples_per_pixel = SAMPLES_PER_PIXEL;

    // Scene
    HittableList scene;

    p3d lookfrom(13.0, 2.0, 3.0);
    p3d lookat(0.0, 0.0, 0.0);
    f64 vertical_field_of_view = 40.0;
    f64 aperture = 0.0;
    RGB background(0.0, 0.0, 0.0);

    switch (6) {
        case 1:
            scene                   = random_scene();
            background              = RGB( 0.7, 0.8, 1.0);
            lookfrom                = p3d(13.0, 2.0, 3.0);
            lookat                  = p3d( 0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            aperture                = 0.1;
            break;
        case 2:
            scene                   = two_spheres();
            background              = RGB( 0.7, 0.8, 1.0);
            lookfrom                = p3d(13.0, 2.0, 3.0);
            lookat                  = p3d( 0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            break;
        case 3:
            scene                   = two_perlin_spheres();
            background              = RGB( 0.7, 0.8, 1.0);
            lookfrom                = p3d(13.0, 2.0, 3.0);
            lookat                  = p3d( 0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            break;
        case 4:
            scene                   = earth();
            background              = RGB( 0.7, 0.8, 1.0);
            lookfrom                = p3d(13.0, 2.0, 3.0);
            lookat                  = p3d( 0.0, 0.0, 0.0);
            vertical_field_of_view  = 20.0;
            break;
        case 5:
            scene                   = simple_light();
            samples_per_pixel       = 400;
            lookfrom                = p3d(26.0, 3.0, 6.0);
            lookat                  = p3d( 0.0, 2.0, 0.0);
            vertical_field_of_view  = 20.0;
            break;
        case 6:
            scene                   = cornell_box();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 1000;
            lookfrom                = p3d(278.0, 278.0, -800.0);
            lookat                  = p3d(278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
            break;
        case 7:
            scene                   = cornell_smoke();
            aspect_ratio            = 1.0;
            image_width             = 600;
            samples_per_pixel       = 200;
            lookfrom                = p3d(278.0, 278.0, -800.0);
            lookat                  = p3d(278.0, 278.0,    0.0);
            vertical_field_of_view  = 40.0;
            break;
        default:
        case 8:
            scene                   = final_scene();
            aspect_ratio            = 1.0;
            image_width             = 800;
            samples_per_pixel       = 10000;
            lookfrom                = p3d(478.0, 278.0, -600.0);
            lookat                  = p3d(278.0, 278.0, 0.0);
            vertical_field_of_view  = 40.0;
            break;
    }

    const i32 image_height = image_width / aspect_ratio;

    // BVHNode bvh(scene, 0.0, 1.0);

    // Camera
    const Vec3 viewup(0.0, 1.0, 0.0);
    const f64 focus_distance = 10.0;

    const Camera camera(lookfrom, lookat, viewup, vertical_field_of_view, aspect_ratio, aperture, focus_distance, 0.0, 1.0);

    // Render
    std::cout.tie(0);
    std::cout << "P3\n";
    std::cout << image_width << ' ' << image_height << '\n';
    std::cout << "255\n";

    for (i32 j = image_height - 1; j >= 0; --j) {
        fprintf(stderr, "Rendering: %d lines remaining\n", j);
        for (i32 i = 0; i < image_width; ++i) {
            RGB pixel_color(0.0, 0.0, 0.0);
            for (i32 s = 0; s < samples_per_pixel; ++s) {
                const f64 u = (i + random_f64()) / (image_width - 1);
                const f64 v = (j + random_f64()) / (image_height - 1);
                pixel_color += camera.get_ray(u, v).color(scene, background, MAX_DEPTH);
            }
            std::cout << pixel_color / samples_per_pixel << '\n';
        }
    }
    fprintf(stderr, "\nDone.\n");
    return 0;
}
