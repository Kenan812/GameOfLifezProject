#include "includes/game_circular.h"

BOARD* prepare_board_circular(int rows, int cols, int** pos, int points_alive){
    BOARD* board = initialize_board(rows, cols);
    fill_board_borders(board);
    fill_board(board, pos, points_alive);
    return board;
}


void perform_step_circular(BOARD* board) {
    BOARD* tmp_board = initialize_board(board->rows-2, board->cols-2);  // -2 for border
    // 1 s because of border
    for (int i = 1; i < board->rows-1; i++) {
        for (int j = 1; j < board->cols-1; j++) {
            int test;

            int count = 0;
            // counting neighbors

            if (board->board_content[i-1][j-1] == 1) count++;
            else if (board->board_content[i-1][j-1] == 2) {
                if (i == 1 && j == 1 && board->board_content[board->rows-2][board->cols-2] == 1) count++;
                else if (j == 1 && board->board_content[i-1][board->cols-2] == 1) count++;
                else if (i == 1 && board->board_content[board->rows-2][j-1] == 1) count++;
            }

            if (board->board_content[i-1][j] == 1) count++;
            else if (board->board_content[i-1][j] == 2) {
                if (board->board_content[board->rows-2][j] == 1) count++;
            }

            if (board->board_content[i-1][j+1] == 1) count++;
            else if (board->board_content[i-1][j+1] == 2) {
                if (i == 1 && j == board->cols-2 && board->board_content[board->rows-2][1] == 1) count++;
                else if (j == board->cols-2 && board->board_content[i-1][1] == 1) count++;
                else if (i == 1 && board->board_content[board->rows-2][j+1] == 1) count++;
            }

            if (board->board_content[i][j-1] == 1) count++;
            else if (board->board_content[i][j-1] == 2) {
                if (board->board_content[i][board->cols-2] == 1) count++;
            }

            if (board->board_content[i][j+1] == 1) count++;
            else if (board->board_content[i][j+1] == 2) {
                if (board->board_content[i][1] == 1) count++;
            }

            if (board->board_content[i+1][j-1] == 1) count++;
            else if (board->board_content[i+1][j-1] == 2) {
                if (i == board->rows-2 && j == 1 && board->board_content[1][board->cols-2] == 1) count++;
                else if (j == 1 && board->board_content[i+1][board->cols-2] == 1) count++;
                else if (i == board->rows-2 && board->board_content[1][j-1] == 1) count++;
            }

            if (board->board_content[i+1][j] == 1) count++;
            else if (board->board_content[i+1][j] == 2) {
                if (board->board_content[1][j] == 1) count++;
            }
            
            if (board->board_content[i+1][j+1] == 1) count++;
            else if (board->board_content[i+1][j+1] == 2) {
                if (i == board->rows-2 && j == board->cols-2 && board->board_content[1][1] == 1) count++;
                else if (j == board->cols-2 && board->board_content[i+1][1] == 1) count++;
                else if (i == board->rows-2 && board->board_content[1][j+1] == 1) count++;
            }


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



void start_game_circular(BOARD* board) {
    while(1) {
        system("clear");
        draw_board(*board);

        perform_step_circular(board);
        sleep(1);
    }
}


