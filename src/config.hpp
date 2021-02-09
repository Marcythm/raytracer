#pragma once

/* Concepts library */
#include <concepts>

/* Coroutines Library */
// #include <coroutines>

/* Utilities library */
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <functional>
#include <utility>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <any>
#include <optional>
#include <variant>
#include <compare>
#include <version>
// #include <source_location>

/* Dynamic memory management */
#include <new>
#include <memory>
#include <scoped_allocator>
// #include <memory_resource>

/* Numeric limits */
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>

/* Error handling */
#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>

/* Strings library */
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
// #include <cuchar>
#include <string>
#include <string_view>
#include <charconv>
// #include <format>

/* Containers library */
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <span>

/* Iterators library */
#include <iterator>

/* Ranges library */
// #include <ranges>

/* Algorithms library */
#include <algorithm>
#include <execution>

/* Numerics library */
#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cfenv>
#include <bit>
#include <numbers>

/* Localization library */
#include <locale>
#include <clocale>
#include <codecvt>

/* Input/output library */
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
// #include <syncstream>
#include <strstream>
#include <iomanip>
#include <streambuf>
#include <cstdio>

/* Filesystem library */
#include <filesystem>

/* Regular Expressions library */
#include <regex>

/* Atomic Operations library */
#include <atomic>

/* Thread support library */
#include <thread>
// #include <stop_token>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>
#include <semaphore>
#include <latch>
#include <barrier>

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

#ifdef _LIBCPP_MEMORY
template <typename T>
	using ptr = std::shared_ptr<T>;
#else
template <typename T>
	using ptr = T *;
#endif

#ifdef _LIBCPP_VECTOR
template <typename T>
	using Vec = std::vector<T>;
#endif

#ifdef _LIBCPP_STRING
	using str = std::string;
#endif


/* classes */

struct p3d;
struct Vec3;
struct RGB;
struct Ray;
struct Camera;

struct HitRecord;
struct Hittable;
struct Sphere;
struct HittableList;

struct Material;
struct Lambertian;
struct Metal;
struct Dielectric;

enum class diffuse_render_method: bool {
    hemispherical_scattering = false,
    true_lambertian_reflection = true,
};

/* constants */
namespace constants {

	// Image
	constexpr f64 aspect_ratio = 3.0 / 2.0; // 16.0 / 9.0;
	constexpr i32 image_width = 1200; // 400;
	constexpr i32 image_height = static_cast<i32>(image_width / aspect_ratio);
	constexpr i32 samples_per_pixel = 500; // 100;
	constexpr i32 max_depth = 50;
	constexpr f64 GAMMA = 2;

	// Camera
	constexpr f64 viewport_height = 2.0;
	constexpr f64 viewport_width = viewport_height * aspect_ratio;
	constexpr f64 focal_length = 1.0;


	constexpr f64 infinity = std::numeric_limits<f64>::infinity();
	constexpr f64 eps = 1e-5;
	constexpr f64 pi = 3.1415926535897932385;

	constexpr diffuse_render_method diffuse_render_method_type = diffuse_render_method::true_lambertian_reflection;
}
