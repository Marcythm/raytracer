#include "config.hpp"
#include "lib.hpp"

#include "ray.hpp"
#include "camera.hpp"
#include "aabb.hpp"
#include "bvhnode.hpp"

#include "hittable.hpp"
#include "sphere.hpp"
#include "moving_sphere.hpp"

#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"
#include "diffuse_light.hpp"

#include "texture.hpp"
#include "solid_color.hpp"
#include "checker_texture.hpp"
#include "noise_texture.hpp"
#include "image_texture.hpp"

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
					const auto center2 = center + Vec3(0.0, random_f64(0.0, 0.5), 0.0);
					scene.push(MovingSphere(center, center2, 0.0, 1.0, 0.2, sphere_material));
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
	scene.push(Sphere(p3d(0.0, 1.0, 0.0), 1.0, material1));

	const auto material2 = std::make_shared<Lambertian>(RGB(0.4, 0.2, 0.1));
	scene.push(Sphere(p3d(-4.0, 1.0, 0.0), 1.0, material2));

	const auto material3 = std::make_shared<Metal>(RGB(0.7, 0.6, 0.5), 0.0);
	scene.push(Sphere(p3d(4.0, 1.0, 0.0), 1.0, material3));

	return scene;
}

auto two_spheres() -> HittableList {
	HittableList hittables;

	const auto checker = std::make_shared<CheckerTexture>(RGB(0.2, 0.3, 0.1), RGB(0.9, 0.9, 0.9));
	hittables.push(Sphere(p3d(0.0, -10.0, 0.0), 10.0, std::make_shared<Lambertian>(checker)));
	hittables.push(Sphere(p3d(0.0,  10.0, 0.0), 10.0, std::make_shared<Lambertian>(checker)));

	return hittables;
}

auto two_perlin_spheres() -> HittableList {
	HittableList hittables;

	const auto pertext = std::make_shared<NoiseTexture>(4.0);
	hittables.push(Sphere(p3d(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(pertext)));
	hittables.push(Sphere(p3d(0.0, 2.0, 0.0), 2.0, std::make_shared<Lambertian>(pertext)));

	return hittables;
}

auto earth() -> HittableList {
	HittableList hittables;

	const auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
	const auto earth_surface = std::make_shared<Lambertian>(earth_texture);
	hittables.push(Sphere(p3d(0.0, 0.0, 0.0), 2.0, earth_surface));

	return hittables;
}

auto main() -> i32 {
	// Scene
	HittableList scene;

	p3d lookfrom(13.0, 2.0, 3.0);
	p3d lookat(0.0, 0.0, 0.0);
	f64 vertical_field_of_view = 40.0;
	f64 aperture = 0.0;
	RGB background(0.0, 0.0, 0.0);

	switch (0) {
		case 1:
			scene = random_scene();
			background = RGB(0.7, 0.8, 1.0);
			lookfrom = p3d(13.0, 2.0, 3.0);
			lookat = p3d(0.0, 0.0, 0.0);
			vertical_field_of_view = 20.0;
			aperture = 0.1;
			break;
		case 2:
			scene = two_spheres();
			background = RGB(0.7, 0.8, 1.0);
			lookfrom = p3d(13.0, 2.0, 3.0);
			lookat = p3d(0.0, 0.0, 0.0);
			vertical_field_of_view = 20.0;
			break;
		case 3:
			scene = two_perlin_spheres();
			background = RGB(0.7, 0.8, 1.0);
			lookfrom = p3d(13.0, 2.0, 3.0);
			lookat = p3d(0.0, 0.0, 0.0);
			vertical_field_of_view = 20.0;
			break;
		case 4:
			scene = earth();
			background = RGB(0.7, 0.8, 1.0);
			lookfrom = p3d(13.0, 2.0, 3.0);
			lookat = p3d(0.0, 0.0, 0.0);
			vertical_field_of_view = 20.0;
			break;
		default:
		case 5:
			background = RGB(0.0, 0.0, 0.0);
			break;
	}

	BVHNode bvh(scene, 0.0, 1.0);

	// Camera
	const Vec3 viewup(0.0, 1.0, 0.0);
	const f64 focus_distance = 10.0;

	const Camera camera(lookfrom, lookat, viewup, vertical_field_of_view, ASPECT_RATIO, aperture, focus_distance, 0.0, 1.0);

	// Render
	std::cout.tie(0);
	std::cout << "P3\n";
	std::cout << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n';
	std::cout << "255\n";

	for (i32 j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		fprintf(stderr, "Rendering: %d lines remaining\n", j);
		for (i32 i = 0; i < IMAGE_WIDTH; ++i) {
			RGB pixel_color(0.0, 0.0, 0.0);
			for (i32 s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				const f64 u = (i + random_f64()) / (IMAGE_WIDTH - 1);
				const f64 v = (j + random_f64()) / (IMAGE_HEIGHT - 1);
				pixel_color += camera.get_ray(u, v).color(bvh, background, MAX_DEPTH);
			}
			std::cout << pixel_color << '\n';
		}
	}
	fprintf(stderr, "\nDone.\n");
	return 0;
}
