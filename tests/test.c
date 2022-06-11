#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "CUnit/Basic.h"

typedef struct game_board {
    int rows;  // increased by 2 because of the border
    int cols;  // increased by 2 because of the border
    int** board_content;
} BOARD;


static FILE* temp_file = NULL;

void perform_step_clipped(BOARD* board);
void perform_step_circular(BOARD* board);

BOARD* initialize_board(int rows, int cols);
void fill_board_borders(BOARD* board);
void fill_board(BOARD* board, int** pos, int points_alive);
void copy_board(BOARD* source, BOARD* dest);
void free_board(BOARD* board);

void testPERFORM_STEP_CLIPPED(void);
void testPERFORM_STEP_CIRCULAR(void);

void testINTIALIZE_BOARD(void);
void testFILL_BOARD(void);
void testFILL_BOARD_BORDERS(void);
void testCOPY_BOARD(void);
void testFREE_BOARD(void);


int init_suite(void) 
{
    if ((temp_file = fopen("temp.txt", "w+")) == NULL ) return -1;
    return 0;   
}

int clean_suite(void)
{
    if (0 != fclose(temp_file)) return -1;
    temp_file = NULL;
    return 0;
}




int main()
{
    CU_pSuite suite = NULL, suiteBoard;
    if ( CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    suite = CU_add_suite("Suite", init_suite, clean_suite);
    suiteBoard = CU_add_suite("SuiteBoard", init_suite, clean_suite);
    if (suite == NULL || suiteBoard == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
        
    if (CU_add_test(suite, "test of perform_step_clipped()",testPERFORM_STEP_CLIPPED) == NULL ||
        CU_add_test(suite, "test of perform_step_circular()",testPERFORM_STEP_CIRCULAR) == NULL ||
        CU_add_test(suiteBoard, "test of intialize_board()",testINTIALIZE_BOARD) == NULL ||
        CU_add_test(suiteBoard, "test of fill_board_borders()",testFILL_BOARD_BORDERS) == NULL ||
        CU_add_test(suiteBoard, "test of fill_board()",testFILL_BOARD) == NULL ||
        CU_add_test(suiteBoard, "test of copy_board()",testCOPY_BOARD) == NULL 
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}


void perform_step_clipped(BOARD* board) {
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

void fill_board(BOARD* board, int** pos, int points_alive) {
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

void free_board(BOARD* board){
    free(board);
}


void testINTIALIZE_BOARD(void) {
    BOARD* board = initialize_board(10,10);
    CU_ASSERT(board!=NULL || board->board_content!=NULL);
}

void testFILL_BOARD_BORDERS(void) {
    BOARD* board = initialize_board(5,5);
    fill_board_borders(board);
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            if (i == 0 || i == board->rows-1 || j == 0 || j == board->cols-1) {
                CU_ASSERT_EQUAL(board->board_content[i][j], 2);
            }
        }
    }
}

void testFILL_BOARD(void) {
    BOARD* board = initialize_board(10,10);
    fill_board_borders(board); 

    int points_alive = 13;
    int **pos = (int**)malloc(points_alive * sizeof(int*));
    CU_ASSERT(pos!=NULL)
    for (int i = 0; i < points_alive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
        CU_ASSERT(pos[i]!=NULL)
    }

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


    fill_board(board, pos, points_alive);
    for (int i = 0 ; i < points_alive; i++) {
        CU_ASSERT_EQUAL(board->board_content[pos[i][0]][pos[i][1]], 1);
    }
    
}

void testCOPY_BOARD(void){
    BOARD* board = initialize_board(10,10);  // -2 for border
    BOARD* tmp_board = initialize_board(10,10);  // -2 for border

    fill_board_borders(board); 

    int points_alive = 13;
    int **pos = (int**)malloc(points_alive * sizeof(int*));
    CU_ASSERT(pos!=NULL)
    for (int i = 0; i < points_alive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
        CU_ASSERT(pos[i]!=NULL)
    }

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

    fill_board(board, pos, points_alive);

    copy_board(board, tmp_board);
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            CU_ASSERT_EQUAL(board->board_content[i][j], tmp_board->board_content[i][j]);
        }
    }
}

void testFREE_BOARD(void){
    CU_ASSERT(1);
}

void testPERFORM_STEP_CLIPPED(void) {
    BOARD *board = initialize_board(10,10);
    
    int points_alive = 13;
    int **pos = (int**)malloc(points_alive * sizeof(int*));
    for (int i = 0; i < points_alive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
    }

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

    // board = prepare_board(10, 10, pos, point_alive);
    board = initialize_board(10,10);
    fill_board_borders(board);
    fill_board(board, pos, points_alive);

    perform_step_clipped(board);
    CU_ASSERT(board->board_content!=NULL);
}

void testPERFORM_STEP_CIRCULAR(void) {
    BOARD *board = initialize_board(10,10);
    
    int points_alive = 13;
    int **pos = (int**)malloc(points_alive * sizeof(int*));
    for (int i = 0; i < points_alive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
    }

    pos[0][0] = 2; pos[0][1] = 1;
    pos[1][0] = 5-2; pos[1][1] = 3-2;
    pos[2][0] = 5-2; pos[2][1] = 4-2;
    pos[3][0] = 5-2; pos[3][1] = 5-2;
    pos[4][0] = 5-2; pos[4][1] = 6-2;
    pos[5][0] = 5-2; pos[5][1] = 7-2;
    pos[6][0] = 5-2; pos[6][1] = 8-2;
    pos[7][0] = 4-2; pos[7][1] = 5-2;
    pos[8][0] = 3-2; pos[8][1] = 5-2;
    pos[9][0] = 1; pos[9][1] = 2;
    pos[10][0] = 6-2; pos[10][1] = 5-2;
    pos[11][0] = 7-2; pos[11][1] = 5-2;
    pos[12][0] = 1; pos[12][1] = 1;

    // board = prepare_board(10, 10, pos, point_alive);
    board = initialize_board(10,10);
    fill_board_borders(board);
    fill_board(board, pos, points_alive);

    perform_step_circular(board);
    CU_ASSERT(board->board_content!=NULL);
}


