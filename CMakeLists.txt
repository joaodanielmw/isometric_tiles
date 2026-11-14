cmake_minimum_required(VERSION 3.31)
project(isometric LANGUAGES C)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_executable(
    ${PROJECT_NAME}
    src/main.c
    src/app.c
)

target_link_libraries(
    ${PROJECT_NAME}
    SDL3::SDL3
    SDL3_image::SDL3_image
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    include
)
