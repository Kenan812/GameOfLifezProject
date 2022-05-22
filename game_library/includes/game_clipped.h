#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "board.h"
#include "../../draw_animation_library/includes/board_drawer.h"

/* CLIPPED VERSION OF THE GAME */


// Prepare board for the game
//      Initialize board, fill borders
// Parameters: 
//      rows: number of rows
//      cols: number of cols
// Return: pointer to created board
BOARD* prepare_board(int rows, int cols, int** pos, int points_alive);


// Performs step of the game by modifying the board
// Parameters: 
//      rows: number of rows
void perform_step(BOARD* board);


// Starts game of life
// Parameters: 
//      rows: number of rows
void start_game_clipped(BOARD* board);


