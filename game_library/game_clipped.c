#include "includes/game_clipped.h"

BOARD* prepare_board(int rows, int cols, int** pos, int points_alive){
    BOARD* board = initialize_board(rows, cols);
    fill_board_borders(board);
    fill_board(board, pos, points_alive);
    return board;
}



void perform_step(BOARD* board) {
    BOARD* tmp_board = initialize_board(board->rows-2, board->cols-2);  // -2 for border
    // 1 s because of border
    for (int i = 1; i < board->rows-1; i++) {
        for (int j = 1; j < board->cols-1; j++) {
            int test;

            int count = 0;
            // counting neighbors
            if (board->board_content[i-1][j-1] == 1) count++;
            if (board->board_content[i-1][j] == 1) count++;
            if (board->board_content[i-1][j+1] == 1) count++;
            if (board->board_content[i][j-1] == 1) count++;
            if (board->board_content[i][j+1] == 1) count++;
            if (board->board_content[i+1][j-1] == 1) count++;
            if (board->board_content[i+1][j] == 1) count++;
            if (board->board_content[i+1][j+1] == 1) count++;

            // dead cell becomes alive
            if (board->board_content[i][j] == 0 && count == 3) {
                tmp_board->board_content[i][j] = 1;
            }

            // alive cell stays alive
            else if (board->board_content[i][j] == 1 && (count==3 || count==2)) {
                tmp_board->board_content[i][j] = 1;
            }

            // alive cell becomes dead
            else {
                tmp_board->board_content[i][j] = 0;
            }
        }
    }

    copy_board(tmp_board, board);
    free_board(tmp_board);
}



void start_game(BOARD* board) {
    while(1) {
        system("clear");
        //print_board(board);
        draw_board(*board);

        perform_step(board);
        sleep(1);
    }
}
