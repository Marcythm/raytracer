#include "config.hpp"
#include "p3d.hpp"
#include "vec3.hpp"
#include "rgb.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittablelist.hpp"
#include "camera.hpp"

auto ray_color(const Ray &ray, const Hittable &world) -> RGB {
	if (const auto &[succ, rec] = world.hit(ray, 0.0, infinity); succ)
		return 0.5 * RGB(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	const f64 t = 0.5 * (ray.direction().unit().y() + 1.0);
	return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}

auto main() -> i32 {
	// Image
	constexpr f64 aspect_ratio = 16.0 / 9.0;
	constexpr i32 image_width = 400;
	constexpr i32 image_height = static_cast<i32>(image_width / aspect_ratio);
	constexpr i32 samples_per_pixel = 100;

	// World
	HittableList world;
	world.push(std::make_shared<Sphere>(p3d(0, 0, -1), 0.5));
	world.push(std::make_shared<Sphere>(p3d(0, -100.5, -1), 100));

	// Camera
	constexpr f64 viewport_height = 2.0;
	constexpr f64 viewport_width = viewport_height * aspect_ratio;
	constexpr f64 focal_length = 1.0;
	constexpr Camera camera(viewport_height, viewport_width, focal_length);

	// Render
	std::cout.tie(0);
	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

	for (i32 j = image_height - 1; j >= 0; --j) {
		std::cerr << "Scanlines remaining: " << j << '\n' << std::flush;
		for (i32 i = 0; i < image_width; ++i) {
			RGB pixel_color(0, 0, 0);
			for (i32 s = 0; s < samples_per_pixel; ++s) {
				const f64 u = (i + random_f64()) / (image_width - 1);
				const f64 v = (j + random_f64()) / (image_height - 1);
				pixel_color += ray_color(camera.get_ray(u, v), world);
			}
			pixel_color.print(std::cout, samples_per_pixel) << '\n';
		}
	}
	std::cerr << "\nDone.\n";
	return 0;
}
