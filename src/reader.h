#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

void read_grid(char *filename, uint8_t *grid, int *cols, int *rows);
void read_png(char *filename, uint8_t *grid, int *cols, int *rows);
void write_grid(char *filename, uint8_t *grid, int cols, int rows);