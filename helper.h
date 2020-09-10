#ifndef IMAGE_TRANSFORMER_HELPER_H
#define IMAGE_TRANSFORMER_HELPER_H

#include <iostream>

#define DEBUG

template <typename Func>
inline void if_debug(Func&& f) {
#ifdef DEBUG
    f();
#endif
}

template <typename ...ArgsT>
inline void out(ArgsT ...args) {
    (std::cout << ... << args) << std::endl;
}

#endif //IMAGE_TRANSFORMER_HELPER_H
