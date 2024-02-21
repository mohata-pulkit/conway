#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "reader.h"

void read_grid(char *filename, uint8_t *grid, int *cols, int *rows)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error: File not found\n");
		return;
	}
	fscanf(file, "%d %d", rows, cols);
	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *cols; j++)
		{
			int cell;
			fscanf(file, "%d", &cell);
			if (cell == 1)
			{
				grid[(i * (*cols)) + j] = 0b10000000;
			}
			else
			{
				grid[(i * (*cols)) + j] = 0b00000000;
			}
			// printf("[%d][%d]:%d\n", i, j, cell);
		}
	}
	fclose(file);
}

void read_png(char *filename, uint8_t *grid, int *cols, int *rows)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_Surface *image;
	image = IMG_Load(filename);
	if (image == NULL)
	{
		printf("Error: File not found\n");
		return;
	}
	*cols = image->w;
	*rows = image->h;
	uint8_t *newGrid = (uint8_t *)malloc((*cols) * (*rows) * sizeof(uint8_t));
	for (int i = 0; i < *rows; i++)
	{
		for (int j = 0; j < *cols; j++)
		{

			Uint8 *pPixel = ((Uint8 *)image->pixels + i * image->pitch + j * image->format->BytesPerPixel);
			Uint32 pixelData = *(Uint32 *)pPixel;
			SDL_Color color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
			SDL_GetRGB(pixelData, image->format, &color.r, &color.g, &color.b);
			if (color.r > 127 && color.g > 127 && color.b > 127)
			{
				newGrid[(i * (*cols)) + j] = 0b10000000;
			}
			else
			{
				newGrid[(i * (*cols)) + j] = 0b00000000;
			}
		}
	}
	for (int i = 0; i < (*rows) * (*cols); i++)
	{
		grid[i] = newGrid[i];
	}
	SDL_FreeSurface(image);
}

void write_grid(char *filename, uint8_t *grid, int cols, int rows)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error: File not found\n");
		return;
	}
	fprintf(file, "%d %d\n", rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if ((grid[i * cols + j] | 0b00001111) & 0b10000000)
			{
				fprintf(file, "1 ");
			}
			else
			{
				fprintf(file, "0 ");
			}
		}
		fprintf(file, "\n");
	}
	fclose(file);
}