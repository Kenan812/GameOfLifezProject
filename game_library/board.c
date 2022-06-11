#include "includes/board.h"

BOARD* initialize_board(int rows, int cols) {
    BOARD* board;
    board = (BOARD*)malloc(1);

    // +2 for border
    rows+=2;
    cols+=2;

    board->rows = rows;
    board->cols = cols;
    
    board->board_content = (int**)malloc(rows * sizeof(int*));
    if (board->board_content == NULL){ fprintf(stderr, "Momory allocation error"); return NULL; }
    for (int i = 0; i < rows; i++) {
        board->board_content[i] = (int*)malloc(cols * sizeof(int));
        if (board->board_content[i] == NULL) { fprintf(stderr, "Momory allocation error"); return NULL; }
        for (int j = 0; j < cols; j ++) {
            board->board_content[i][j] = 0;
        }
    }

    return board;
}


void fill_board_borders(BOARD* board) {
    for (int i = 0; i < board->cols; i++) {
        board->board_content[0][i] = 2;
        board->board_content[board->rows-1][i] = 2;
    }

    for (int i = 0; i < board->rows; i++) {
        board->board_content[i][0] = 2;
        board->board_content[i][board->cols-1] = 2;
    }
}


// MUST BE REWRITEN AFTER ADDING DRAW LIBRARY 
void print_board(BOARD* board) {
    for (int i = 1; i < board->rows-1; i++) {
        for (int j = 1; j < board->cols-1;j++) {
            printf("%d ", board->board_content[i][j]);
        }
        printf("\n");
    }
}


void fill_board(BOARD* board, int** pos, int points_alive){
    for (int i = 0; i < points_alive; i++) {
        if (pos[i][0] > 0 && pos[i][0] < board->rows-1 && pos[i][1] > 0 && pos[i][1] < board->cols-1)
            board->board_content[pos[i][0]][pos[i][1]] = 1;
    }
}


void copy_board(BOARD* source, BOARD* dest) {
    for (int i = 0; i < source->rows; i++) {
        for (int j = 0; j < source->cols; j++) {
            dest->board_content[i][j] = source->board_content[i][j];
        }
    }
}


void free_board(BOARD* board) {
    free(board);
}

