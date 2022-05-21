add_library(game_library STATIC board.c)
target_include_directories(game_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
