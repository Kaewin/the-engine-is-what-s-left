#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <termios.h>

#define WIDTH 60
#define HEIGHT 20

char grid[HEIGHT][WIDTH] = {0};

int left_wall = 0;
int right_wall = WIDTH - 1;

int top_wall = 0;
int bottom_wall = HEIGHT - 1;

static struct termios orig_termios;   // remember the normal settings

int running = 1;

int dir_r = 0;
int dir_c = 1;


void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);   // restore
}

void enable_raw_mode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);   // save current settings
    atexit(disable_raw_mode);                 // auto-restore on exit

    struct termios raw = orig_termios;        // work on a copy
    raw.c_lflag &= ~(ICANON | ECHO);          // turn OFF line-buffering + echo
    raw.c_cc[VMIN]  = 0;   // read() may return with 0 bytes...
    raw.c_cc[VTIME] = 0;   // ...and never waits
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}


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

    enable_raw_mode();

    while (running) {
        printf("\033[H\033[J");
        print_grid();
        fflush(stdout);

        grid[head_r][head_c] = '.';

        char c;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            switch (c) {
                case 'w':
                    dir_r = -1;
                    dir_c = 0;
                    break;
                case 's':
                    dir_r = 1;
                    dir_c = 0;
                    break;
                case 'a':
                    dir_r = 0;
                    dir_c = -1;
                    break;
                case 'd':
                    dir_r = 0;
                    dir_c = 1;
                    break;
                case 'q':
                    running = 0;
                    break;
            }
        }

        head_r += dir_r;
        head_c += dir_c;

        if (head_r <= top_wall || head_r >= bottom_wall ||
            head_c <= left_wall || head_c >= right_wall) {
            break;
        }

        grid[head_r][head_c] = '@';

        usleep(200000);
    }

    disable_raw_mode();
}

int main(void) {
    printf("Hello, world!\n");

    run_snake();

    return 0;
}