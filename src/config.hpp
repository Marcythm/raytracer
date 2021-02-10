#pragma once

/* Concepts library */
#include <concepts>

/* Coroutines Library */
// #include <coroutines>

/* Utilities library */
#include <cstdlib>
// #include <csignal>
// #include <csetjmp>
// #include <cstdarg>
// #include <typeinfo>
// #include <typeindex>
#include <type_traits>
// #include <bitset>
#include <functional>
#include <utility>
// #include <ctime>
// #include <chrono>
#include <cstddef>
#include <initializer_list>
// #include <tuple>
// #include <any>
#include <optional>
// #include <variant>
// #include <compare>
// #include <version>
// #include <source_location>

/* Dynamic memory management */
#include <new>
#include <memory>
// #include <scoped_allocator>
// #include <memory_resource>

/* Numeric limits */
// #include <climits>
// #include <cfloat>
// #include <cstdint>
// #include <cinttypes>
#include <limits>

/* Error handling */
#include <exception>
#include <stdexcept>
#include <cassert>
// #include <system_error>
// #include <cerrno>

/* Strings library */
// #include <cctype>
// #include <cwctype>
// #include <cstring>
// #include <cwchar>
// #include <cuchar>
#include <string>
#include <string_view>
// #include <charconv>
// #include <format>

/* Containers library */
// #include <array>
#include <vector>
// #include <deque>
// #include <list>
// #include <forward_list>
// #include <set>
// #include <map>
// #include <unordered_set>
// #include <unordered_map>
// #include <stack>
// #include <queue>
// #include <span>

/* Iterators library */
// #include <iterator>

/* Ranges library */
// #include <ranges>

/* Algorithms library */
#include <algorithm>
// #include <execution>

/* Numerics library */
#include <cmath>
// #include <complex>
// #include <valarray>
#include <random>
#include <numeric>
// #include <ratio>
// #include <cfenv>
// #include <bit>
// #include <numbers>

/* Localization library */
// #include <locale>
// #include <clocale>
// #include <codecvt>

/* Input/output library */
// #include <iosfwd>
// #include <ios>
// #include <istream>
// #include <ostream>
#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <syncstream>
// #include <strstream>
// #include <iomanip>
// #include <streambuf>
// #include <cstdio>

/* Filesystem library */
// #include <filesystem>

/* Regular Expressions library */
// #include <regex>

/* Atomic Operations library */
// #include <atomic>

/* Thread support library */
// #include <thread>
// #include <stop_token>
// #include <mutex>
// #include <shared_mutex>
// #include <future>
// #include <condition_variable>
// #include <semaphore>
// #include <latch>
// #include <barrier>

/* ---------- C++ headers ---------- */

/* ---------- type aliases ---------- */

using i8	=	signed char;		// int8_t;
using i16	=	signed short;		// int16_t;
using i32	=	signed int;			// int32_t;
using i64	=	signed long long;	// int64_t;

using u8	=	unsigned char;		// uint8_t;
using u16	=	unsigned short;		// uint16_t;
using u32	=	unsigned int;		// uint32_t;
using u64	=	unsigned long long;	// uint64_t;

using f32	=	float;
using f64	=	double;
using f80	=	long double;


template <typename T>
	using ptr = std::shared_ptr<T>;

template <typename T>
	using Vec = std::vector<T>;

using str = std::string;


/* classes */

struct p3d;
struct Vec3;
struct RGB;

struct Ray;
struct Camera;
struct AABB;
struct BVHNode;

struct HitRecord;
struct Hittable;
struct HittableList;
struct Sphere;
struct MovingSphere;
struct XYAARectangle;
struct YZAARectangle;
struct ZXAARectangle;

struct Material;
struct Lambertian;
struct Metal;
struct Dielectric;
struct DiffuseLight;

struct Texture;
struct SolidColor;
struct CheckerTexture;
struct NoiseTexture;
struct IMageTexture;

enum class diffuse_render_method: bool {
    hemispherical_scattering = false,
    true_lambertian_reflection = true,
};

/* constants */
namespace constants {

	// Image
#ifdef HIGH_QUALITY
	constexpr f64 ASPECT_RATIO = 3.0 / 2.0;
	constexpr i32 IMAGE_WIDTH = 1200;
	constexpr i32 IMAGE_HEIGHT = static_cast<i32>(IMAGE_WIDTH / ASPECT_RATIO);
	constexpr i32 SAMPLES_PER_PIXEL = 500;
	constexpr i32 MAX_DEPTH = 50;
	constexpr f64 GAMMA = 2.0;
#else
	constexpr f64 ASPECT_RATIO = 16.0 / 9.0;
	constexpr i32 IMAGE_WIDTH = 400;
	constexpr i32 IMAGE_HEIGHT = static_cast<i32>(IMAGE_WIDTH / ASPECT_RATIO);
	constexpr i32 SAMPLES_PER_PIXEL = 100;
	constexpr i32 MAX_DEPTH = 50;
	constexpr f64 GAMMA = 2.0;
#endif

	// Camera
	constexpr f64 VIEWPORT_HEIGHT = 2.0;
	constexpr f64 VIEWPORT_WIDTH = VIEWPORT_HEIGHT * ASPECT_RATIO;
	constexpr f64 FOCAL_LENGTH = 1.0;


	constexpr f64 INF = std::numeric_limits<f64>::infinity();
	constexpr f64 EPS = 1e-5;
	constexpr f64 PI = 3.1415926535897932385;

	constexpr diffuse_render_method DIFFUSE_RENDER_METHOD_TYPE = diffuse_render_method::true_lambertian_reflection;
}

using namespace constants;
