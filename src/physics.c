#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

void find_com(uint8_t *grid, int cols, int rows, int *x, int *y)
{
	int sum_x = 0;
	int sum_y = 0;
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[(i * cols) + j] & 0b10000000)
			{
				sum_x += j;
				sum_y += i;
				count++;
			}
		}
	}
	if (count == 0)
	{
		*x = -1;
		*y = -1;
		return;
	}
	else
	{
		*x = sum_x / count;
		*y = sum_y / count;
	}
}

void find_num_alive(uint8_t *grid, int cols, int rows, int *num_alive)
{
	*num_alive = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[(i * cols) + j] & 0b10000000)
			{
				*num_alive += 1;
			}
		}
	}
}