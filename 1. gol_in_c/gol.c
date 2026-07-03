#include <stdio.h>    // printf
#include <unistd.h>   // usleep
#include <stdlib.h>   // rand, srand
#include <time.h>     // time
#include "gol.h"      // our own interface — good practice to include it

// These are the real definitions and live here exactly ONCE.
// `static` = internal linkage: they're private to this file, an
// implementation detail nobody else can touch. Cleaner than a global.
static int grid[WIDTH][HEIGHT] = {0};
static int secondGrid[WIDTH][HEIGHT] = {0};

void seed(void) {
    for (int r = 0; r < WIDTH; r++) {
        for (int c = 0; c < HEIGHT; c++) {
            grid[r][c] = rand() % 2;
        }
    }
    return;
}

void printGrid(void) {
    printf("\n");
    for (int r = 0; r < WIDTH; r++) {
        for (int c = 0; c < HEIGHT; c++) {
            printf("%d", grid[r][c]);
        }
        printf("\n");
    }
    return;
}

// Given a cell at row r and column c, what are its eight neighbors?
int countNeighbors(int r, int c) {

    int sum = 0;

    // Must skip when dr == 0 and dc == 0 because that's the cell itself (the center)
    for (int dr = -1; dr < 2; dr++) {
        for (int dc = -1; dc < 2; dc++) {
            // Skip the center
            if (dr == 0 && dc == 0) {
                continue;
            }
            // Out of bounds check
            int nr = r + dr;
            int nc = c + dc;
            if (nr < 0 || nr >= HEIGHT || nc < 0 || nc >= WIDTH) {
                continue;
            }
            // Read count
            if (grid[nr][nc] == 1) {
                sum++;
            }
        }
    }
   return sum;
}

void step(void) {
    for (int r = 0; r < WIDTH; r++) {
        for (int c = 0; c < HEIGHT; c++) {
            int n = countNeighbors(r, c);
            if (grid[r][c] == 1) {
                secondGrid[r][c] = (n == 2 || n == 3);
            }
            else {
                secondGrid[r][c] = (n == 3);
            }
        }
    }
    for (int r = 0; r < WIDTH; r++) {
        for (int c = 0; c < HEIGHT; c++) {
            grid[r][c] = secondGrid[r][c];
        }
    }
    return;
}

void runGOL(void) {
    printf("Seeding...\n\n");
    srand((unsigned int) time(NULL));
    seed();
    printf("Now printing the grid:\n\n");

    while (1) {
        printf("\033[H\033[J");
        printGrid();
        fflush(stdout);
        step();
        usleep(200000);
    }
}
