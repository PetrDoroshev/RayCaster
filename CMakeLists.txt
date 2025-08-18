cmake_minimum_required(VERSION 3.19)
project(sg_test C)

set(CMAKE_C_STANDARD 11)

#set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/deps/SDL/x86_64-w64-mingw32/include/SDL2)
#set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/deps/SDL/x86_64-w64-mingw32/lib)

#set(SDL2_IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/deps/SDL2_image/x86_64-w64-mingw32/include/SDL2)
#set(SDL2_IMAGE_LIB_DIR ${PROJECT_SOURCE_DIR}/deps/SDL2_image/x86_64-w64-mingw32/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(sg_test "src/main.c" "src/structs.h" "src/init.h" "src/init.c" "src/defs.h" "src/input.h" "src/input.c" "src/draw.h" "src/draw.c" "src/defs.c" "src/raycast.h" "src/raycast.c"
        "src/timer.c")

target_link_libraries(sg_test SDL2main SDL2 SDL2_image)