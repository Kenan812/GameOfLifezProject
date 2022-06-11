cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
project(game VERSION 1.0)

add_subdirectory(game_library)
add_subdirectory(draw_animation_library)

find_package(SDL2 REQUIRED)
include_directories(game ${SDL2_INCLUDE_DIRS})

add_custom_target(doc ALL COMMAND doxygen Doxyfile VERBATIM)

add_executable(game main.c draw_animation_library/board_drawer.c)
target_link_libraries(game PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(game PUBLIC game_library)
target_link_libraries(game PUBLIC draw_animation_library)
