ifdef HIGH_QUALITY
CXXFLAGS=-Wall -Wextra -std=c++2a -O2 -DHIGH_QUALITY
else
CXXFLAGS=-Wall -Wextra -std=c++2a -O2
endif

all: *.hpp *.cpp utilities/*.hpp hittable/*.hpp material/*.hpp texture/*.hpp hittable/*.cpp material/*.cpp texture/*.cpp
	clang++ ${CXXFLAGS}                                                     \
		-I. -Iutilities -Ihittable       -Imaterial       -Itexture         \
		./*.cpp           hittable/*.cpp   material/*.cpp   texture/*.cpp   \
		-o main
