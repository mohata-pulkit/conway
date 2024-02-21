#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

void find_com(uint8_t *grid, int cols, int rows, int *x, int *y);
void find_num_alive(uint8_t *grid, int cols, int rows, int *num_alive);