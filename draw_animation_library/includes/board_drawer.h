#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../../game_library/includes/board.h"

#define RED "\x1b[1;31m"
#define YELLOW "\x1b[1;33m"
#define WHITE "\x1b[1;0m"
#define BLUE "\x1b[1;34m"

void draw_board(BOARD board);
