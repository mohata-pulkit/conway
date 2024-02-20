#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void save_grid_png(uint8_t *grid, int cols, int rows, int gen);
void save_grid_bmp(uint8_t *grid, int cols, int rows, int gen);