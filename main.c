#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "game_library/includes/board.h"
#include "game_library/includes/game_clipped.h"
#include "game_library/includes/game_circular.h"
#include "draw_animation_library/includes/board_drawer.h"


/* Return 1 for clipped game
 Return 2 for circular game*/
int choose_game_type();


void start_game(BOARD* board, int type);



int main() {
    int game_type = choose_game_type();
    BOARD* board;
    start_game(board, game_type);
    free_board(board);
    return 0;
}

int choose_game_type() {
    int type;
    while(1) {
        system("clear");
        printf(RED); printf("\tChoose game type\n");
        printf(WHITE); printf("1-Clipped\n2-Circular\n\n");
        printf("Enter category: ");
        type = getchar();
        getchar();
        if (type == 49 || type == 50) break;
    }
    printf(WHITE);
    return type - 48;
}


void start_game(BOARD* board, int type) {
    srand(time(0));
    printf("Preparing board...\n");
}


