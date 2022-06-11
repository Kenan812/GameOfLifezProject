#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "board.h"
#include "../../draw_animation_library/includes/board_drawer.h"

/* CIRCULAR VERSION OF THE GAME */


// Prepare board for the game
//      Initialize board, fill borders
// Parameters: 
//      rows:             number of rows
//      cols:             number of cols
//      pos:              positions of initially alive pixels
//      points_alive:     initial number of alive pixels
// Return: pointer to created board
BOARD* prepare_board_circular(int rows, int cols, int** pos, int points_alive);


// Performs step of the game by modifying the board
// Parameters: 
//      board: border of the game
void perform_step_circular(BOARD* board);

