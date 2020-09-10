//
// Created by avdosev on 10.09.2020.
//

#include <memory>
#include <algorithm>
#include "jpeg.h"
#include "error.h"

extern "C" {
#include <jpeglib.h>
}

using auto_close_file = std::unique_ptr<FILE, decltype(&fclose)>;

image read_image(std::string src) {
    auto_close_file image_file(fopen(src.c_str(), "rb"), &fclose);
    if (image_file == nullptr) {
        throw file_not_found("file not found");
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    struct jpeg_decompress_struct info; //for our jpeg info
    struct jpeg_error_mgr err;          //the error handler

    info.err = jpeg_std_error(&err);
    jpeg_create_decompress(&info);   // fills info structure

    jpeg_stdio_src(&info, image_file.get());
    jpeg_read_header(&info, TRUE);

    jpeg_start_decompress(&info);    // decompress the file

    size_t width = info.output_width;
    size_t height = info.output_height;
    size_t channels = info.num_components;

    image img(height, width);
    std::vector<uint8_t> row(info.output_width*channels);
    while (info.output_scanline < info.output_height) {
        auto rowptr = row.data();
        jpeg_read_scanlines(&info, &rowptr, 1);
        for (size_t i = 0; i < width; i++) {
            image::pixel_type pixel;
            pixel.resize(channels);
            for (size_t ch = 0; ch < channels; ch++) {
                pixel[ch] = row[i*channels+ch];
            }
            img.pixels[info.output_scanline].emplace_back(std::move(pixel));
        }
    }

    jpeg_finish_decompress(&info);   //finish decompressing
    jpeg_destroy_decompress(&info);

    return img;
}