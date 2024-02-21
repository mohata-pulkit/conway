#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mpeg.h"

SDL_Surface *surface_from_grid(uint8_t *grid, int cols, int rows)
{
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface *surface = SDL_CreateRGBSurface(0, cols, rows, 32, 0, 0, 0, 0);
	for (int i = 0; i < cols * rows; i++)
	{
		uint8_t color;
		color = grid[i] & 0b10000000;
		// color = grid[i] & 0b00001111;
		uint8_t r = color / 0b10000000 * 255;
		uint8_t g = color / 0b10000000 * 255;
		uint8_t b = color / 0b10000000 * 255;
		// uint8_t r = (color * 255) / 0b00001000;
		// uint8_t g = (color * 255) / 0b00001000;
		// uint8_t b = (color * 255) / 0b00001000;
		((uint32_t *)surface->pixels)[i] = (r << 16) | (g << 8) | b;
	}
	return surface;
}

void save_grid_png(uint8_t *grid, int cols, int rows, int gen)
{
	char filename[100];
	sprintf(filename, "data/imgs/%d.png", gen);
	SDL_Surface *surface = surface_from_grid(grid, cols, rows);
	IMG_SavePNG(surface, filename);
	SDL_FreeSurface(surface);
}

void save_grid_bmp(uint8_t *grid, int cols, int rows, int gen)
{
	char filename[100];
	sprintf(filename, "data/imgs/%d.bmp", gen);
	SDL_Surface *surface = surface_from_grid(grid, cols, rows);
	SDL_SaveBMP(surface, filename);
	SDL_FreeSurface(surface);
}