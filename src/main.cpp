#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittablelist.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

auto main() -> i32 {
	// World
	const auto material_ground = std::make_shared<Lambertian>(RGB(0.8, 0.8, 0.0));
	const auto material_center = std::make_shared<Lambertian>(RGB(0.1, 0.2, 0.5));
	const auto material_left   = std::make_shared<Dielectric>(1.5);
	const auto material_right  = std::make_shared<Metal>(RGB(0.8, 0.6, 0.2), 0.0);

	HittableList world;
	world.push(std::make_shared<Sphere>(p3d( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.push(std::make_shared<Sphere>(p3d( 0.0,    0.0, -1.0),   0.5, material_center));
	world.push(std::make_shared<Sphere>(p3d(-1.0,    0.0, -1.0),   0.5, material_left));
	world.push(std::make_shared<Sphere>(p3d(-1.0,    0.0, -1.0), -0.45, material_left));
	world.push(std::make_shared<Sphere>(p3d( 1.0,    0.0, -1.0),   0.5, material_right));

	// Camera
	const p3d lookfrom(3, 3, 2);
	const p3d lookat(0, 0, -1);
	const Vec3 viewup(0, 1, 0);
	const f64 focus_distance = (lookfrom - lookat).length();
	const f64 aperture = 2.0;

	const Camera camera(lookfrom, lookat, viewup, 20, constants::aspect_ratio, aperture, focus_distance);
	// const Camera camera(p3d(-2, 2, 1), p3d(0, 0, -1), Vec3(0, 1, 0), 90, constants::aspect_ratio);

	// Render
	std::cout.tie(0);
	std::cout << "P3\n";
	std::cout << constants::image_width << ' ' << constants::image_height << '\n';
	std::cout << "255\n";


	for (i32 j = constants::image_height - 1; j >= 0; --j) {
		std::cerr << "Scanlines remaining: " << j << '\n' << std::flush;
		for (i32 i = 0; i < constants::image_width; ++i) {
			RGB pixel_color(0, 0, 0);
			for (i32 s = 0; s < constants::samples_per_pixel; ++s) {
				const f64 u = (i + random_f64()) / (constants::image_width - 1);
				const f64 v = (j + random_f64()) / (constants::image_height - 1);
				pixel_color += camera.get_ray(u, v).color(world, constants::max_depth);
			}
			std::cout << pixel_color << '\n';
		}
	}
	std::cerr << "\nDone.\n";
	return 0;
}
