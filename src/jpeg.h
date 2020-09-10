#ifndef IMAGE_TRANSFORMER_JPEG_H
#define IMAGE_TRANSFORMER_JPEG_H

#include <string>
#include "image.h"

image read_image(std::string src);
void write_image(std::string dest, image img, int quality);

#endif //IMAGE_TRANSFORMER_JPEG_H
