#ifndef IMAGE_TRANSFORMER_JPEG_H
#define IMAGE_TRANSFORMER_JPEG_H

#include <string>
#include <vector>

struct image {
    using pixel_type = std::vector<uint8_t>;
    using pixels_type = std::vector<std::vector<pixel_type>>;

    image(size_t height, size_t weight) {
        pixels.resize(height);
        for (auto& row: pixels) {
            row.reserve(weight);
        }
    }

    size_t height() noexcept  {
        return pixels.size();
    }

    size_t weight() noexcept {
        return height() ? pixels[0].size() : 0;
    }

    pixels_type pixels;
};

image read_image(std::string src);
void write_image(std::string src);

#endif //IMAGE_TRANSFORMER_JPEG_H
