#include <iostream>
#include "jpeg.h"


template <typename ...ArgsT>
void out(ArgsT ...args) {
    (std::cout << ... << args) << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        out("args not found");
        return -1;
    } else {

    }
    return 0;
}



