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
    static_assert(ax != axis::vertical, "Vertical axis not supported");
    std::reverse(img.pixels.begin(), img.pixels.end());
    return img;
}

#endif //IMAGE_TRANSFORMER_IMAGE_OPERATIONS_H
