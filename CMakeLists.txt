cmake_minimum_required(VERSION 3.10.2)
project(raytracer-cpp)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_COMPILER  "/usr/local/opt/llvm/bin/clang++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

if (DEFINED ENV{HIGH_QUALITY})
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHIGH_QUALITY")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/third_party/
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/src/utilities/
    ${PROJECT_SOURCE_DIR}/src/hittable/
    ${PROJECT_SOURCE_DIR}/src/material/
    ${PROJECT_SOURCE_DIR}/src/texture/
    ${PROJECT_SOURCE_DIR}/src/transform/
    ${PROJECT_SOURCE_DIR}/src/medium/
    ${PROJECT_SOURCE_DIR}/src/pdf/
)
file(GLOB src_dir
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utilities/*.cpp
    ${PROJECT_SOURCE_DIR}/src/hittable/*.cpp
    ${PROJECT_SOURCE_DIR}/src/material/*.cpp
    ${PROJECT_SOURCE_DIR}/src/texture/*.cpp
    ${PROJECT_SOURCE_DIR}/src/transform/*.cpp
    ${PROJECT_SOURCE_DIR}/src/medium/*.cpp
    ${PROJECT_SOURCE_DIR}/src/pdf/*.cpp
)

add_executable(raytracer-cpp ${src_dir} src/main.cpp)
