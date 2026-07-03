#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 60
#define HEIGHT 20

char grid[HEIGHT][WIDTH] = {0};

int left_wall = 0;
int right_wall = WIDTH - 1;

int top_wall = 0;
int bottom_wall = HEIGHT - 1;

// Going to first start by initializing the board to all .'s
// Then worry about the border
void build_border(void) {

    // Fill in the board
    for(int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            grid[r][c] = '.';
        }
    }

    // Fill in the walls
    for(int r = 0; r < HEIGHT; r++) {
        grid[r][left_wall] = '*';
        grid[r][right_wall] = '*';
    }
    for(int c = 0; c < WIDTH; c++) {
        grid[top_wall][c] = '*';
        grid[bottom_wall][c] = '*';
    }
    return;
}

void print_grid(void) {
    printf("\n");
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%c", grid[r][c]);
        }
        printf("\n");
    }
    return;
}

void run_snake(void) {
    build_border();

    int head_r = HEIGHT / 2;
    int head_c = WIDTH / 2;
    grid[head_r][head_c] = '@';

    srand((unsigned int) time(NULL));
    printf("Now printing the grid:\n\n");

    while (1) {
        printf("\033[H\033[J");
        print_grid();
        fflush(stdout);

        grid[head_r][head_c] = '.';

        head_c++;

        if (head_c >= WIDTH - 1) {
            break;
        }

        grid[head_r][head_c] = '@';

        usleep(200000);
    }
}

int main(void) {
    printf("Hello, world!\n");

    run_snake();

    return 0;
}