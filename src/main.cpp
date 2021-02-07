#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittablelist.hpp"
#include "camera.hpp"

auto main() -> i32 {
	// World
	HittableList world;
	world.push(std::make_shared<Sphere>(p3d(0, 0, -1), 0.5));
	world.push(std::make_shared<Sphere>(p3d(0, -100.5, -1), 100));

	// Camera
	constexpr Camera camera(constants::viewport_height, constants::viewport_width, constants::focal_length);

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
