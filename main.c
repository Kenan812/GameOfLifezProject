#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "game_library/includes/board.h"
#include "game_library/includes/game_clipped.h"
#include "game_library/includes/game_circular.h"
#include "draw_animation_library/includes/board_drawer.h"

// initial number of pixels on the board
#define NUM_OF_PIXELS 150000

/* board size */
#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 1280

/* Return 1 for clipped game
 Return 2 for circular game*/
int choose_game_type();

void draw_sdl2(BOARD *board, SDL_Window *window, SDL_Renderer *renderer, int game_type);

void start_game(BOARD *board, int type);

int main()
{
    int game_type = choose_game_type();
    BOARD *board;
    start_game(board, game_type);
    free_board(board);
    return 0;
}

int choose_game_type()
{
    int type;
    while (1)
    {
        system("clear");
        printf(RED);
        printf("\tChoose game type\n");
        printf(WHITE);
        printf("1-Clipped\n2-Circular\n\n");
        printf("Enter category: ");
        type = getchar();
        getchar();
        if (type == 49 || type == 50)
            break;
    }
    printf(WHITE);
    return type - 48;
}

void draw_sdl2(BOARD *board, SDL_Window *window, SDL_Renderer *renderer, int game_type)
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 2, 2);

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    printf("Width: %d\nHeight: %d\n", w, h);

    while (true)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < board->rows; i++)
        {
            for (int j = 0; j < board->cols; j++)
            {
                if (board->board_content[i][j] == 1)
                {
                    SDL_RenderDrawPoint(renderer, j / 2, i / 2);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);

        if (game_type == 1)
            perform_step(board);
        else
            perform_step_circular(board);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void start_game(BOARD *board, int type)
{
    srand(time(0));
    printf("Preparing board...\n");

    int **pos;
    pos = (int **)malloc(NUM_OF_PIXELS * sizeof(int *));
    for (int i = 0; i < NUM_OF_PIXELS; i++)
    {
        pos[i] = (int *)malloc(NUM_OF_PIXELS * sizeof(int));
        pos[i][0] = (rand() % WINDOW_HEIGHT);
        pos[i][1] = (rand() % WINDOW_WIDTH);
    }

    board = prepare_board(WINDOW_HEIGHT, WINDOW_WIDTH, pos, NUM_OF_PIXELS);
    printf("Board ready!\n");

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    draw_sdl2(board, window, renderer, type);
}