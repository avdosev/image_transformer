#include <string>
#include "jpeg.h"
#include "helper.h"
#include "image_operations.h"
#include "error.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        out("args not found");
        out("args: src_image destination_image");
        return -1;
    }

    std::string src = argv[1], dest = argv[2];
    if_debug([&]{
        out("src: ", src);
        out("dest: ", dest);
    });

    try {
        image img = read_image(src);

        if_debug([&]{
            out("height: ", img.height());
            out("width: ", img.width());
        });

        auto img_after_transform =
                rotate_by_axis<axis::horizontal>(
                        rotate_by_axis<axis::vertical>(std::move(img)));
        for (int quality: {1, 20, 50, 75, 90}) {
            write_image(dest + std::to_string(quality) + ".jpg", img_after_transform , quality);
        }
    } catch (file_not_found& err) {
        out(err.what());
        return -2;
    }

    return 0;
}


