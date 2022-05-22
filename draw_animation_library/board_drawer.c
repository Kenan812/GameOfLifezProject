#include "includes/board_drawer.h"

void draw_board(BOARD board) {
    for (int i = 1; i < board.rows-1; i++) {
        for (int j = 1; j < board.cols-1; j++) {
            if (board.board_content[i][j] == 1) printf(RED);
            printf("■ ");
            printf(WHITE);
        }
        printf("\n");
    }
}
 
