all: *.hpp *.cpp utilities/*.hpp hittable/*.hpp material/*.hpp hittable/*.cpp material/*.cpp
	clang++ -Wall -Wextra -std=c++2a -I. -Iutilities -Ihittable -Imaterial -O2 *.cpp hittable/*.cpp material/*.cpp -o main
