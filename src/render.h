#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

void init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height, Uint32 window_flags, Uint32 renderer_flags);
void render_grid(SDL_Renderer *renderer, uint8_t *grid, int cols, int rows, int com_x, int com_y);