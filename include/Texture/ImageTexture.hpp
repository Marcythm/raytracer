#pragma once

#include "Texture/Texture.hpp"

struct ImageTexture: Texture {
    static constexpr i32 BYTES_PER_PIXEL = 3;
    u8 *data;
    i32 width, height;
    i32 bytes_per_scanline;

public:
    // ImageTexture() = default;
    ImageTexture(const char *filename);
    ~ImageTexture() {
        delete[] data;
    }

    auto value(const f64 u, const f64 v, const P3d &p) const -> RGB override;
};
