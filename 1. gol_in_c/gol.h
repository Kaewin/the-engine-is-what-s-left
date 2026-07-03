#ifndef GOL_H
#define GOL_H

#define WIDTH 50
#define HEIGHT 50

// Public interface — just promises that these functions exist.
// No bodies here, so this header can be #included by any number of
// .c files without causing "multiple definition" linker errors.
void seed(void);
void printGrid(void);
int countNeighbors(int r, int c);
void step(void);
void runGOL(void);

#endif
