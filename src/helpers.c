#include "../include/helpers.h"
#include "../include/tic-tac-toe.h"

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

//TODO : Move this out of helpers.c probably doesn't belong here.
//TODO : Probably wasting memory space creating and deleting the struct oftenly. 
struct Move getMouseCollisionOnGrid(Vector2 mousePos, Vector2 gridPos, int gridSize, int gridThickness)
{
	for (int rows = 0; rows < 3; rows++)
	{
		for (int cols = 0; cols < 3; cols++)
		{
			if (CheckCollisionPointRec(mousePos, (Rectangle){rows * (gridSize + gridThickness) + gridPos.x, cols * (gridSize + gridThickness) + gridPos.y, gridSize, gridSize}))
			{
				struct Move attemptedMove = { rows, cols};
				return attemptedMove;
			}
		}
	}
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