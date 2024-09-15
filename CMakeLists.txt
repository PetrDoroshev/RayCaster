cmake_minimum_required(VERSION 3.19)
project(sg_test C)

set(CMAKE_C_STANDARD 11)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SDL/include)
set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/SDL/lib/x86)

set(SDL2_IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/SDL2_image/include)
set(SDL2_IMAGE_LIB_DIR ${PROJECT_SOURCE_DIR}/SDL2_image/lib/x86)


include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(sg_test main.c structs.h init.h init.c defs.h input.h input.c draw.h draw.c defs.c raycast.h raycast.c
        timer.c)

target_link_libraries(sg_test SDL2main SDL2 SDL2_image)