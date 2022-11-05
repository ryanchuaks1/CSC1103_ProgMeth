#include "../../include/tic-tac-toe.h"
#include "../../include/helpers.h"
#include "../../include/screens.h"

enum GameplayMode mode;
void InitGameplayScreen(enum GameplayMode gameMode)
{
    mode = gameMode;
}

void UpdateGameplayScreen()
{
}

void DrawGameplayScreen()
{
    BeginDrawing();

    ClearBackground(WHITE);
    // DrawRectangle(145, 145, (gridSize * 3 + gridThickness * 2) + 20, (gridSize * 3 + gridThickness * 2) + 20, BLACK);

    EndDrawing();
}

static void GenerateBoard()
{
    // Generate black overlay for the board
    DrawRectangle(145, 145, (150 * 3 + 10 * 2) + 20, (150 * 3 + 10 * 2) + 20, BLACK);
}


void UnloadGameplayScreen()
{ 
}

int FinishGameplayScreen()
{

}
