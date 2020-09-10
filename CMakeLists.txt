cmake_minimum_required(VERSION 3.15)
project(image_transformer)

set(CMAKE_CXX_STANDARD 17)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(image_transformer src/main.cpp src/jpeg.cpp src/jpeg.h src/error.h src/helper.h src/image_operations.h src/image.h)

target_link_libraries(image_transformer ${CONAN_LIBS})