#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "render.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height, Uint32 window_flags, Uint32 renderer_flags)
{
	SDL_Init(SDL_INIT_VIDEO);
	*window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags);
	*renderer = SDL_CreateRenderer(*window, -1, renderer_flags);
}

void render_grid(SDL_Renderer *renderer, uint8_t *grid, int cols, int rows, int com_x, int com_y)
{
	int width, height;
	SDL_GetRendererOutputSize(renderer, &width, &height);
	int cell_size = MIN(width / cols, height / rows);
	printf("width: %d, height: %d, cell: %d\n", width, height, cell_size);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	if (com_x != -1 && com_y != -1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_Rect rect = {com_x * cell_size + (cell_size / 4), com_y * cell_size + (cell_size / 4), cell_size / 2, cell_size / 2};
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[j + i * cols] & 0b10000000)
			{
				SDL_Rect rect = {j * cell_size, i * cell_size, cell_size, cell_size};
				// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
	SDL_RenderPresent(renderer);
}