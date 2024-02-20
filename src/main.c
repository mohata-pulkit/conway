#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "reader.h"
#include "mpeg.h"

int truncate(int x, int n)
{
	return (((x % n) + n) % n);
}

uint8_t update_neighbors(uint8_t *grid, int cols, int rows, int x, int y)
{
	uint8_t current = grid[x + y * cols] & 0b10000000;
	int neighbors = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			else
			{
				int col = truncate(x + i, cols);
				int row = truncate(y + j, rows);
				if (grid[col + row * cols] & 0b10000000)
				{
					neighbors++;
				}
			}
		}
	}
	current = current | neighbors;
	return current;
}

void update_neighbors_all(uint8_t *grid, int cols, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			grid[j + i * cols] = update_neighbors(grid, cols, rows, j, i);
		}
	}
}

void init_grid(uint8_t *grid, int cols, int rows)
{
	for (int i = 0; i < cols * rows; i++)
	{
		int x = i % cols;
		int y = i / cols;
		if (pow(x, 2) + pow(y, 2) < pow((cols / 2) - (cols / 8), 2) && pow(x, 2) + pow(y, 2) > pow((cols / 2) - (cols / 4), 2))
		{
			grid[i] = 0b10000000;
		}
		else
		{
			grid[i] = 0b00000000;
		}
		// grid[i] = 0b00000000;
	}
	update_neighbors_all(grid, cols, rows);
}

void update_grid(uint8_t *grid, int cols, int rows)
{
	uint8_t *new_grid = (uint8_t *)malloc(cols * rows * sizeof(uint8_t));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_grid[j + i * cols] = grid[j + i * cols] & 0b10000000;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int neighbors = grid[j + i * cols] & 0b01111111;
			if (new_grid[j + i * cols] == 0b10000000)
			{
				if (neighbors < 2 || neighbors > 3)
				{
					new_grid[j + i * cols] = 0b00000000;
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (neighbors == 3)
				{
					new_grid[j + i * cols] = 0b10000000;
				}
				else
				{
					continue;
				}
			}
		}
	}
	update_neighbors_all(new_grid, cols, rows);
	for (int i = 0; i < cols * rows; i++)
	{
		grid[i] = new_grid[i];
	}
	free(new_grid);
}

int period = 0;

int main(int argc, char *argv)
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	int cols = 800;
	int rows = 800;
	int fps = 120;

	uint8_t *grid = (uint8_t *)malloc(cols * rows * sizeof(uint8_t));

	init_grid(grid, cols, rows);
	init_sdl(&window, &renderer, 800, 800, (SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN), (SDL_RENDERER_ACCELERATED));

	int quit = 0;
	int i = 0;
	while (!quit && i < 1200)
	{
		printf("Generation: %d\n", i);
		render_grid(renderer, grid, cols, rows);
		save_grid_png(grid, cols, rows, i);
		update_grid(grid, cols, rows);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = 1;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = 1;
				}
				// if (event.key.keysym.sym == SDLK_SPACE)
				// {
				// 	update_grid(grid, cols, rows);
				// 	i++;
				// 	printf("Generation: %d\n", i);
				// }
			}
		}
		// SDL_Delay(1000 / fps);
		i++;
	}
	printf("Period: %d\n", period);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free(grid);
}