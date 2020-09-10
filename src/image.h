#ifndef IMAGE_TRANSFORMER_IMAGE_H
#define IMAGE_TRANSFORMER_IMAGE_H

#include <vector>

struct image {
    using pixel_type = std::vector<uint8_t>;
    using pixels_type = std::vector<std::vector<pixel_type>>;

    image() = default;
    image(image&& img) = default;
    image(const image& img) = default;
    image& operator=(const image& img) = default;

    image(size_t height, size_t width) {
        pixels.resize(height);
        for (auto& row: pixels) {
            row.reserve(width);
        }
    }

    size_t height() noexcept  {
        return pixels.size();
    }

    size_t width() noexcept {
        return height() != 0 ? pixels[0].size() : 0;
    }

    pixels_type pixels;
};

#endif //IMAGE_TRANSFORMER_IMAGE_H
