cmake_minimum_required(VERSION 3.10.2)
project(raytracer-cpp)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_COMPILER  "/usr/local/opt/llvm/bin/clang++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

if (DEFINED ENV{HIGH_QUALITY})
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHIGH_QUALITY")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB src_dir ${PROJECT_SOURCE_DIR}/lib/*/*.cpp ${PROJECT_SOURCE_DIR}/lib/*.cpp)

add_executable(raytracer-cpp ${src_dir} lib/main.cpp)
