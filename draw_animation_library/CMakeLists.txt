add_library(draw_animation_library STATIC board_drawer.c)

target_include_directories(draw_animation_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

