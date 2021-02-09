#include "imagetexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party/stb_image.h"
#undef STB_IMAGE_IMPLEMENTATION

ImageTexture::ImageTexture(const char *filename) {
    i32 components_per_pixel = BYTES_PER_PIXEL;
    data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);
    bytes_per_scanline = BYTES_PER_PIXEL * width;
}

auto ImageTexture::value(const f64 u, const f64 v, const p3d &) const -> RGB {
    if (data == nullptr)
        return RGB(0.0, 1.0, 1.0);

    const i32 i = std::min(static_cast<i32>(clamp(u, 0.0, 1.0) * width), width - 1);
    const i32 j = std::min(static_cast<i32>((1.0 - clamp(v, 0.0, 1.0)) * height), height - 1);

    u8 *pixel = data + j * bytes_per_scanline + i * BYTES_PER_PIXEL;
    return RGB(pixel[0], pixel[1], pixel[2]) / 255.0;
}
