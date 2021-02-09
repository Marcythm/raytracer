all: *.hpp *.cpp utilities/*.hpp hittable/*.hpp material/*.hpp texture/*.hpp hittable/*.cpp material/*.cpp texture/*.cpp
	clang++ -Wall -Wextra -std=c++2a -O2                                    \
		-I. -Iutilities -Ihittable       -Imaterial       -Itexture         \
		./*.cpp           hittable/*.cpp   material/*.cpp   texture/*.cpp   \
		-o main
