cmake_minimum_required(VERSION 3.11)
project(GameOfLife)

add_executable(${PROJECT_NAME}
    ./source/main.cpp
    ./source/window.cpp
    ./source/grid.cpp
    ./source/game.cpp
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} SDL2)
