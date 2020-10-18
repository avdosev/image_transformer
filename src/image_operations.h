#ifndef IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H
#define IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H

#include "image.h"
#include <algorithm>

enum class axis {
    vertical,
    horizontal
};

template <axis ax>
image rotate_by_axis(image img) {
    if constexpr (ax == axis::vertical) {
        std::reverse(img.pixels.begin(), img.pixels.end());
    } else if constexpr (ax == axis::horizontal) {
        for (auto& row: img.pixels) {
            std::reverse(row.begin(), row.end());
        }
    } else {
        static_assert(true, "Axis maybe only two");
    }
    return img;
}

image to_gray(image img) {
    for (auto& row: img.pixels) {
        for (auto& pixel: row) {
            pixel[0] *= 0.2989;
            pixel[1] *= 0.5870;
            pixel[2] *= 0.1140;
            pixel[0] += pixel[1]+pixel[2];
            pixel.resize(1);
        }
    }
    return img;
}

#endif //IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H
