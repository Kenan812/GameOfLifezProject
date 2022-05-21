#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    Number of board rows and columns will be incresed by 2, 
    to create boarder around the board, in order not to check
    the border inside the program
*/
/*
    Definition for board:
        0-dead cell
        1-alive cell
        2-border
*/
typedef struct game_board {
    int rows;  // increased by 2 because of the border
    int cols;  // increased by 2 because of the border
    int** board_content;
} BOARD;


// Allocates memory for the board and fills it with zeros
// Parameters: 
//      rows: number of rows
//      cols: number of cols
// Return: pointer to created board
BOARD* initialize_board(int rows, int cols);

// Fills the borders of the board
// Parameters: 
//      board: pointer to the game board
void fill_board_borders(BOARD* board);


// Prints the board without borders
// Parameters: 
//      board: pointer to the game board
void print_board(BOARD* board);


// Fills board with provided alive points
// Parameters: 
//      board: pointer to the game board
//      pos: positions of alive points
//              2d array: pos[row][column]
//      points_alive: number of alive points
void fill_board(BOARD* board, int** pos, int points_alive);


// Copies board values from source to destination
//      Memory for both boards must be allocated, and they must have same number of rows and columns
// Parameters: 
//      source: source to copy
//      dest: destination of the copy
void copy_board(BOARD* source, BOARD* dest);


// Frees the board
// Parameters: 
//      board: pointer to the game board
void free_board(BOARD* board);


