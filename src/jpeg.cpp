//
// Created by avdosev on 10.09.2020.
//

#include <memory>
#include <algorithm>
#include "jpeg.h"
#include "error.h"
#include "helper.h"

extern "C" {
#include <jpeglib.h>
}

using auto_close_file = std::unique_ptr<FILE, decltype(&fclose)>;

image read_image(std::string src) {
    auto_close_file image_file(fopen(src.c_str(), "rb"), &fclose);
    if (image_file == nullptr) {
        throw file_not_found("file " + src + " not found");
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

    if_debug([&]{
        out("width: ", width);
        out("height: ", height);
        out("channels: ", channels);
    });

    image img(height, width);
    std::vector<uint8_t> row(info.output_width*channels);
    while (info.output_scanline < info.output_height) {
        auto rowptr = row.data();
        jpeg_read_scanlines(&info, &rowptr, 1);
        for (size_t i = 0; i < width; i++) {
            image::pixel_type pixel(channels);
            for (size_t ch = 0; ch < channels; ch++) {
                pixel[ch] = row[i*channels+ch];
            }
            img.pixels[info.output_scanline-1].emplace_back(std::move(pixel));
        }
    }

    jpeg_finish_decompress(&info);   //finish decompressing
    jpeg_destroy_decompress(&info);

    return img;
}

void write_image(std::string dest, const image &img, int quality) {
    if_debug([&]{
        out("save file to ", dest);
    });

    auto_close_file image_file(fopen(dest.c_str(), "wb"), &fclose);
    if (image_file == nullptr) {
        throw file_not_found("file " + dest + " not found");
    }

    struct jpeg_compress_struct info;
    struct jpeg_error_mgr jerr;
    info.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&info);

    jpeg_stdio_dest(&info, image_file.get());

    info.image_width = img.width();
    info.image_height = img.height();

    // TODO: this not always correct
    info.input_components = 3;
    info.in_color_space = JCS_RGB;

    jpeg_set_defaults(&info);
    jpeg_set_quality(&info, quality, true);
    jpeg_start_compress(&info, TRUE);

    std::vector<uint8_t> buffer;
    buffer.reserve(info.image_width * info.input_components);
    while (info.next_scanline < info.image_height) {
        for (auto& pixel: img.pixels[info.next_scanline]) {
            std::copy(pixel.begin(), pixel.end(), std::back_inserter(buffer));
        }
        auto row = buffer.data();
        auto row_pointer = &row;
        jpeg_write_scanlines(&info, row_pointer, 1);
        buffer.resize(0);
    }

    jpeg_finish_compress(&info);
    jpeg_destroy_compress(&info);
}