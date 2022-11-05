#include "../include/helpers.h"

int mouseCollide(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CheckCollisionPointRec(mousePos, (Rectangle){i * (gridSize + gridThickness) + gridPos.x, j * (gridSize + gridThickness) + gridPos.y, gridSize, gridSize}))
			{
				return j * 3 + i;
			}
		}
	}
	return -1;
}

// TODO: Swap the input type to an array
int checkButton(Rectangle buttons[3])
{
	Vector2 mousePos = GetMousePosition(); // Gets the current mouse position
	for (int i = 0; i < 3; i++)
	{
		if (CheckCollisionPointRec(mousePos, buttons[i])) // Check is there are any mouse collisions with rectangles (in this case buttons)
			return i;
	}

	return -1;
}