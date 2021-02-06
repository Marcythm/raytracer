#include "config.hpp"
#include "vec3.hpp"
#include "p3d.hpp"
#include "rgb.hpp"
#include "ray.hpp"

constexpr auto hit_sphere(const p3d &center, const f64 radius, const Ray &ray) -> f64 {
	const Vec3 oc = ray.origin() - center;
	const f64 a = ray.direction().length2();
	const f64 half_b = dot(oc, ray.direction());
	const f64 c = oc.length2() - radius * radius;
	const f64 discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return -1.0;
	return (-half_b - std::sqrt(discriminant)) / a;
}

constexpr auto ray_color(const Ray &ray) -> RGB {
	if (const f64 t = hit_sphere(p3d(0, 0, -1), 0.5, ray); t > 0.0) {
		const Vec3 normal = (ray.at(t) - p3d(0, 0, -1)).unit();
		return 0.5 * RGB(normal.x() + 1, normal.y() + 1, normal.z() + 1);
	}
	const f64 t = 0.5 * (ray.direction().unit().y() + 1.0);
	return (1.0 - t) * RGB(1.0, 1.0, 1.0) + t * RGB(0.5, 0.7, 1.0);
}

auto main() -> i32 {
	// Image
	constexpr f64 aspect_ratio = 16.0 / 9.0;
	constexpr i32 image_width = 4000;
	constexpr i32 image_height = static_cast<i32>(image_width / aspect_ratio);

	// Camera
	constexpr f64 viewport_height = 2.0;
	constexpr f64 viewport_width = viewport_height * aspect_ratio;
	constexpr f64 focal_length = 1.0;

	constexpr p3d origin(0, 0, 0);
	constexpr Vec3 horizontal(viewport_width, 0, 0);
	constexpr Vec3 vertical(0, viewport_height, 0);
	constexpr p3d lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);


	// Render
	std::cout.tie(0);
	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

	for (i32 j = image_height - 1; j >= 0; --j) {
		std::cerr << "Scanlines remaining: " << j << '\n' << std::flush;
		for (i32 i = 0; i < image_width; ++i) {
			f64 u = f64(i) / (image_width - 1);
			f64 v = f64(j) / (image_height - 1);
			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);

			std::cout << ray_color(ray) << '\n';
		}
	}
	std::cerr << "\nDone.\n";
	return 0;
}
