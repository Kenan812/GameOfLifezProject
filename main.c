#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define RED_BOLD "\x1b[1;31m"
#define WHITE_BOLD "\x1b[1;0m"

// Size of board without borders
#define BOARD_ROWS 10
#define BOARD_COLS 10
 
// #define BOARD_ROWS 40
// #define BOARD_COLS 40


/*
    Definition for board:
        0-dead cell
        1-alive cell
        2-border
*/

void fillBoardBorders(int** board, int rows, int cols) {
    for (int i = 0; i < cols; i++) {
        board[0][i] = 2;
        board[rows-1][i] = 2;
    }

    for (int i = 0; i < rows; i++) {
        board[i][0] = 2;
        board[i][cols-1] = 2;
    }
} 

void printBoard(int** board, int rows, int cols) {
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols-1;j++) {
            if (board[i][j] == 1) printf(RED_BOLD);
            printf("■ ");
            printf(WHITE_BOLD);
        }
        printf("\n");
    }
}

void fillBoard(int** board, int rows, int cols, int** pos, int pointsAlive) {
    int counter = 1;
    for (int i = 0; i < pointsAlive; i++) {
        board[pos[i][0]][pos[i][1]] = 1;
    }
}

void copyBoard(int** source, int** dest, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dest[i][j] = source[i][j];
        }
    }
}

void performStep(int** board, int** tmpBoard, int rows, int cols) {
    // 1 s because of border
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols-1; j++) {
            int test;

            int count = 0;
            // counting neighbors
            if (board[i-1][j-1] == 1) count++;
            if (board[i-1][j] == 1) count++;
            if (board[i-1][j+1] == 1) count++;
            if (board[i][j-1] == 1) count++;
            if (board[i][j+1] == 1) count++;
            if (board[i+1][j-1] == 1) count++;
            if (board[i+1][j] == 1) count++;
            if (board[i+1][j+1] == 1) count++;
            // printf("i:%d-j:%d===%d     ",i,j, count);
            // if (j == cols-2) printf("\n");

            // dead cell becomes alive
            if (board[i][j] == 0 && count == 3) {
                tmpBoard[i][j] = 1;
            }

            // alive cell stays alive
            else if (board[i][j] == 1 && (count==3 || count==2)) {
                tmpBoard[i][j] = 1;
            }

            // alive cell becomes dead
            else {
                tmpBoard[i][j] = 0;
            }
        }
    }

}

void startGame(int** board, int rows, int cols) {
    // int aaa = 0;
    while(1) {
        system("clear");
        // clrscr();
        printBoard(board, rows, cols);


        int** tmpBoard;
        tmpBoard = (int**)malloc(rows * sizeof(int*));  // +2 for border 
        if (tmpBoard == NULL){ printf("Memory allocation error"); return; }
        for (int i = 0; i < rows; i++) {
            tmpBoard[i] = (int*)malloc(cols * sizeof(int));
            if (tmpBoard[i] == NULL) { printf("Memory allocation error"); return; }
            for (int j = 0; j < cols; j ++) {
                tmpBoard[i][j] = 0;
            }
        }

        // copyBoard(board, tmpBoard, rows, cols);
        performStep(board, tmpBoard, rows, cols);

        copyBoard(tmpBoard, board, rows, cols);

        // printBoard(board, rows, cols);
        printf("\n\n\n");

        for (int i = 0; i < rows; i++) 
            free(tmpBoard[i]);
        free(tmpBoard);

        // aaa++;
        // break;

        sleep(1);
    }
}

int main() {
    printf(WHITE_BOLD);
    // printf("■");


    int **board;

    // Actual size of board
    int rows = BOARD_ROWS + 2;    
    int cols = BOARD_COLS + 2;

    board = (int**)malloc(rows * sizeof(int*));  // +2 for border 
    if (board == NULL){ printf("Memory allocation error"); return 1; }
    for (int i = 0; i < rows; i++) {
        board[i] = (int*)malloc(cols * sizeof(int));
        if (board[i] == NULL) { printf("Memory allocation error"); return 1;}
        for (int j = 0; j < cols; j ++) {
            board[i][j] = 0;
        }
    }

    fillBoardBorders(board, rows, cols);

    // Allocation of alive positions on board
    int pointAlive = 39;
    int **pos = (int**)malloc(pointAlive * sizeof(int*));
    if (pos == NULL){ printf("Memory allocation error"); return 1; }
    for (int i = 0; i < pointAlive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
        if (pos[i] == NULL) { printf("Memory allocation error"); return 1;}
    }

    // input 1
    pos[0][0] = 5; pos[0][1] = 2;
    pos[1][0] = 5; pos[1][1] = 3;
    pos[2][0] = 5; pos[2][1] = 4;
    pos[3][0] = 5; pos[3][1] = 5;
    pos[4][0] = 5; pos[4][1] = 6;
    pos[5][0] = 5; pos[5][1] = 7;
    pos[6][0] = 5; pos[6][1] = 8;
    pos[7][0] = 4; pos[7][1] = 5;
    pos[8][0] = 3; pos[8][1] = 5;
    pos[9][0] = 2; pos[9][1] = 5;
    pos[10][0] = 6; pos[10][1] = 5;
    pos[11][0] = 7; pos[11][1] = 5;
    pos[12][0] = 8; pos[12][1] = 5;



    fillBoard(board, rows, cols, pos, pointAlive);
    // printBoard(board, rows, cols);

    printf("\n\n\n");
    startGame(board, rows, cols);

    // free all pointers
    for (int i = 0; i < rows; i++) 
        free(board[i]);
    free(board);

    for (int i = 0; i < pointAlive; i++) 
        free(pos[i]);
    free(pos);

    return 0;
}