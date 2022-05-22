#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game_library/includes/board.h"
#include "game_library/includes/game_clipped.h"
#include "game_library/includes/game_circular.h"
#include "draw_animation_library/includes/board_drawer.h"

// Return 1 for clipped game
// Return 2 for circular game
int choose_game_type();


int main() {
    int game_type = choose_game_type();

    int point_alive = 13;
    int **pos = (int**)malloc(point_alive * sizeof(int*));
    if (pos == NULL){ printf("Memory allocation error"); return 1; }
    for (int i = 0; i < point_alive; i++) {
        pos[i] = (int*)malloc(2 * sizeof(int));
        if (pos[i] == NULL) { printf("Memory allocation error"); return 1;}
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

    BOARD* board;

    // Clipped
    if (game_type == 1) {
        board = prepare_board(10, 10, pos, point_alive);
        start_game_clipped(board);
    } else if (game_type == 2) {
        // start circular game
        board = prepare_board_circular(10, 10, pos, point_alive);
        start_game_circular(board);
    }

    free_board(board);
    return 0;
}


int choose_game_type() {
    int type;
    while(1) {
        system("clear");
        printf(RED); printf("\tChoose difficulty\n");
        printf(WHITE); printf("1-Clipped\n2-Circular\n\n");
        printf("Enter category: ");
        type = getchar();
        getchar();
        // scanf("%c", &type);
        if (type == 49 || type == 50) break;
    }
    printf(WHITE);
    return type - 48;
}


